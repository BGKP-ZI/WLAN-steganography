#include <Network/WLAN.hh>

namespace Network {

WLAN::WLAN(const std::string &interface) : interface(interface) {
  setup_interface();
}

#ifndef WINDOWS_SYSTEM
void WLAN::linux_setup_interface(void) {
  try {
    if (ifconfig.socket_id == std::size_t(-1)) {
      close(ifconfig.socket_id);
    }

    struct ifreq ifr;

    if ((ifconfig.socket_id = socket(AF_PACKET, SOCK_RAW, 0)) ==
        std::size_t(-1)) {
      throw std::runtime_error("Can\'t open socket : " +
                               std::string(std::strerror(errno)));
    }

    strcpy(ifr.ifr_name, interface.data());
    if (ioctl(ifconfig.socket_id, SIOGIFINDEX, &ifr) < 0)
      throw std::runtime_error("Failed to fetch ifindex: " +
                               std::string(strerror(errno)));
    ifconfig.interface_index = ifr.ifr_ifindex;

    if (ioctl(ifconfig.socket_id, SIOCGIFHWADDR, &ifr) == -1)
      throw std::runtime_error("Failed to fetch hardware address: " +
                               std::string(strerror(errno)));

    for (std::size_t i = 0; i < ifconfig.MAC.address_length(); ++i)
      ifconfig.MAC.addr[i] = ifr.ifr_hwaddr.sa_data[i];

    if (ioctl(ifconfig.socket_id, SIOCGIFMTU, &ifr) == -1)
      throw std::runtime_error("Failed to get the MTU: " +
                               std::string(strerror(errno)));

    ifconfig.mtu = ifr.ifr_mtu;

    struct sockaddr_ll sll;
    memset(&sll, 0, sizeof(sll));
    sll.sll_family = AF_PACKET;
    sll.sll_ifindex = ifconfig.interface_index;
    sll.sll_protocol = htons(ETH_P_ALL);
    if (bind(ifconfig.socket_id, (struct sockaddr *)&sll, sizeof(sll)) < 0)
      throw std::runtime_error("Failed to bind the socket: " +
                               std::string(strerror(errno)));
  } catch (const std::exception &exp) {
    std::cout << exp.what() << std::endl;
  }
}
#else
void WLAN::windows_setup_interface(void) {}
#endif

void WLAN::setup_interface(void) {
#ifndef WINDOWS_SYSTEM
  linux_setup_interface();
#else
#endif
}

WLAN::~WLAN() {
  if (ifconfig.socket_id == std::size_t(-1)) {
    close(ifconfig.socket_id);
  }
}

WLAN::WLAN_header::WLAN_header(const MACAddress &to_addr,
                               const IfConfig &ifconfig) {
  std::memmove(dest.addr.data(), to_addr.addr.data(), dest.address_length());
  std::memmove(src.addr.data(), ifconfig.MAC.addr.data(), src.address_length());
}

std::size_t WLAN::WLAN_header::size() const {
  return src.address_length() + dest.address_length() + sizeof(type);
}

void WLAN::IfConfig::dump(std::ostream &out) const {
  out << "Socket ID : " << socket_id << std::endl;
  out << "Interface Index : " << interface_index << std::endl;
  out << "MAC : " << MAC.to_string(true) << std::endl;
  out << "MTU : " << mtu << std::endl;
}

void WLAN::WLAN_header::cp2buff(char *buff) const noexcept {
  
  std::memmove(buff, dest.addr.data(), dest.address_length());
  std::memmove(buff + dest.address_length(), src.addr.data(),
               dest.address_length());
  std::memmove(buff + 2 * dest.address_length(), &type, sizeof(type));
}

void WLAN::ifconfig_info(std::ostream &out) const noexcept {
  ifconfig.dump(out);
}

void WLAN::set_toaddr(const MACAddress &addr,
                      struct sockaddr_ll &to) const noexcept {
  to.sll_family = AF_PACKET;
  to.sll_ifindex = ifconfig.interface_index;
  std::memmove(&(to.sll_addr), addr.addr.data(), addr.address_length());
  to.sll_halen = addr.address_length();
}

void WLAN::probe(const IPv4Address &addr) {
  std::string ip_addr = addr.to_string();
  ARP_scanner::send_and_parse(interface.data(), ip_addr.data());
}

void WLAN::send(const MACAddress &addr, const std::string &msg) const {
  WLAN_header header(addr, ifconfig);

  char *send_buff = new char[header.size() + msg.size()];
  header.cp2buff(send_buff);

  struct sockaddr_ll to;
  set_toaddr(addr, to);

  for (std::size_t i = 0, end = msg.size(), hd_sz = header.size(); i < end; ++i) {
    send_buff[hd_sz + i] = msg[i];
  }

  int sentlen = sendto(ifconfig.socket_id, send_buff, header.size() + msg.size(),
                       0, (sockaddr *)&to, sizeof(to));
  if (sentlen == -1) {
    delete[] send_buff;
    printf("rofl\n");
    throw std::runtime_error("Failed to send a message");
  }

  delete[] send_buff;
}

void WLAN::recieve(std::string &msg) const {
  char *recv_msg = new char[ifconfig.mtu];

  struct sockaddr_ll from;
  socklen_t fromlen = sizeof(from);
  for (;;) {
    for (;;) {
      std::memset(recv_msg, 0, ifconfig.mtu);
      if (recvfrom(ifconfig.socket_id, recv_msg, ifconfig.mtu, 0,
                  (struct sockaddr *)&from, &fromlen) == -1) {
        std::cout << "Can not recv msg" << std::endl;
        usleep(10000);
      } else {
        break;
      }
    }

    WLAN_header *wlan_hdr = (WLAN_header *)recv_msg;
    msg = std::string(recv_msg + wlan_hdr->size());
    std::cout << "Header size = " << wlan_hdr->size()
      << " | msg : " << msg << std::endl;
  }
  delete [] recv_msg;
}

void WLAN::ARP_scanner::sendArpRequest(const char *iface, const char *targetIP, const char *sourceIP) {
  int sockfd = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ALL));
  if (sockfd == -1)
    throw std::runtime_error("Socket creation error");

  struct ifreq ifr;
  strncpy(ifr.ifr_name, iface, IFNAMSIZ - 1);
  if (ioctl(sockfd, SIOCGIFHWADDR, &ifr) == -1) {
    close(sockfd);
    throw std::runtime_error("Error getting MAC address");
  }

  WLAN_header ethHeader;
  ARP_header arpHeader;

  memcpy(ethHeader.src.addr.data(), "\xff\xff\xff\xff\xff\xff", MAC_ADDR_LENGTH); // Broadcast MAC
  memcpy(ethHeader.dest.addr.data(), ifr.ifr_hwaddr.sa_data, MAC_ADDR_LENGTH);
  ethHeader.type = htons(ETHERTYPE_ARP);

  arpHeader.hardwareType = htons(ARPHRD_ETHER);
  arpHeader.protocolType = htons(ETH_P_IP);
  arpHeader.hardwareSize = MAC_ADDR_LENGTH;
  arpHeader.protocolSize = IP_ADDR_LENGTH;
  arpHeader.opCode = htons(ARP_REQUEST);
  memcpy(arpHeader.senderMac, ifr.ifr_hwaddr.sa_data, MAC_ADDR_LENGTH);
  inet_pton(AF_INET, sourceIP, arpHeader.senderIP); // put here sender ip address
  inet_pton(AF_INET, targetIP, arpHeader.targetIP);

  char packet[ETHERNET_HEADER_LENGTH + arpHeader.size];
  memcpy(packet, &ethHeader, ETHERNET_HEADER_LENGTH);
  memcpy(packet + ETHERNET_HEADER_LENGTH, &arpHeader, arpHeader.size);

  struct sockaddr_ll socket_address;
  memset(&socket_address, 0, sizeof(socket_address));
  socket_address.sll_ifindex = if_nametoindex(iface);
  socket_address.sll_family = AF_PACKET;
  if (sendto(sockfd, packet, sizeof(packet), 0, (struct sockaddr*)&socket_address, sizeof(socket_address)) == -1) {
    close(sockfd);
    throw std::runtime_error("Error sending ARP request");
  }

  close(sockfd);
}

bool WLAN::ARP_scanner::parseArpResponse(const char *buffer) {
  ARP_header* arpHeader = (ARP_header*)(buffer + ETHERNET_HEADER_LENGTH);

  if (ntohs(arpHeader->opCode) != ARP_REPLY)
    return false;

  for (int i = 0; i < MAC_ADDR_LENGTH; ++i) {
    printf("%02x:", arpHeader->senderMac[i]);
  }
  std::cout << std::endl;

  // std::stringstream ss;
  // for(std::size_t i = 0, end = MACAddress::address_length(); i < end; ++i)
  //   ss << std::hex << (int)arpHeader->senderMac[i] << (i + 1!= end? ":" : "");
  // std::string key = ss.str();

  std::cout << "Sender IP Address: ";
  for (int i = 0; i < IP_ADDR_LENGTH; ++i) {
    printf("%d.", arpHeader->senderIP[i]);
  }
  std::cout << std::endl;

  return true;
}

void WLAN::ARP_scanner::send_and_parse(const char *iface, const char *targetIp) {
  sendArpRequest(iface, targetIp, "192.168.0.113");

  char buffer[ETH_FRAME_LEN];
  int sockfd = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ALL));
  if (sockfd == -1)
    throw std::runtime_error("Socket creation error");

  ssize_t bytesRead = recv(sockfd, buffer, sizeof(buffer), 0);
  if (bytesRead == -1) {
    close(sockfd);
    throw std::runtime_error("Error receiving ARP response");
  }

  parseArpResponse(buffer);

  close(sockfd);
}

} // namespace Network