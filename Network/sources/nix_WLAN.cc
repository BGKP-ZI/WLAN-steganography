#include <WLAN.hh>

namespace Network {

WLAN::WLAN(const std::string &interface) : interface(interface) {
  setup_interface();
}

void WLAN::setup_interface(void) {
  try {
    if (ifconfig.socket_id == std::size_t(-1)) {
      close(ifconfig.socket_id);
    }

    struct ifreq ifr;

    if ((ifconfig.socket_id = socket(AF_PACKET, SOCK_RAW, 0)) == std::size_t(-1)) {
      throw std::runtime_error("Can\'t open socket : " + std::string(std::strerror(errno)));
    }

    strcpy(ifr.ifr_name, interface.data());
    if (ioctl(ifconfig.socket_id, SIOGIFINDEX, &ifr) < 0)
      throw std::runtime_error("Failed to fetch ifindex: " + std::string(strerror(errno)));
    ifconfig.interface_index = ifr.ifr_ifindex;

    if (ioctl(ifconfig.socket_id, SIOCGIFHWADDR, &ifr) == -1)
      throw std::runtime_error("Failed to fetch hardware address: " + std::string(strerror(errno)));

    for (std::size_t i = 0; i < ifconfig.MAC.size(); ++i)
      ifconfig.MAC.addr[i] = ifr.ifr_hwaddr.sa_data[i];

    if (ioctl(ifconfig.socket_id, SIOCGIFMTU, &ifr) == -1)
      throw std::runtime_error("Failed to get the MTU: " + std::string(strerror(errno)));

    ifconfig.mtu = ifr.ifr_mtu;

    struct sockaddr_ll sll;
    memset(&sll, 0, sizeof(sll));
    sll.sll_family = AF_PACKET;
    sll.sll_ifindex = ifconfig.interface_index;
    sll.sll_protocol = htons(ETH_P_ALL);
    if (bind(ifconfig.socket_id, (struct sockaddr *)&sll, sizeof(sll)) < 0)
      throw std::runtime_error("Failed to bind the socket: " + std::string(strerror(errno)));
  } catch (const std::exception &exp) {
    std::cout << exp.what() << std::endl;
  }
}

WLAN::~WLAN() {
  if (ifconfig.socket_id == std::size_t(-1)) {
    close(ifconfig.socket_id);
  }
}

void WLAN::ifconfig_info(std::ostream &out) const noexcept {
  ifconfig.dump(out);
}

void WLAN::set_toaddr(const MACAddress &addr, struct sockaddr_ll &to) const noexcept {
  to.sll_family = AF_PACKET;
  to.sll_ifindex = ifconfig.interface_index;
  std::memmove(&(to.sll_addr), addr.addr.data(), addr.size());
  to.sll_halen = addr.size();
}

void WLAN::send(const MACAddress &addr, const std::string &msg) const {
  WLAN_header header(addr, ifconfig);

  if (ifconfig.mtu < header.size) {
    throw std::runtime_error("It isn\'t possible to send messages with MTU size < ethernet header");
  }
  
  char *send_buff = new char[ifconfig.mtu+1];

  for (std::size_t buffer_size = 0, buffer_end = msg.size(), step = ifconfig.mtu - header.size; buffer_size < buffer_end; buffer_size += step) {
    
    for (std::size_t i = 0, i_end = ifconfig.mtu + 1; i < i_end; ++i) 
      send_buff[i] = 0;
    
    header.cp2buff(send_buff);

    struct sockaddr_ll to;
    set_toaddr(addr, to);

    std::size_t end_idx = std::min(msg.size() - buffer_size, ifconfig.mtu - header.size);
    for (std::size_t i = 0; i < end_idx; ++i) {
      send_buff[header.size + i] = msg[i+buffer_size];
    }

    #if 0
    for (std::size_t i = 0; i < end_idx; ++i) {
      if (i % 14 == 0 && i != 0) printf("\n");
      printf("%02x ", (unsigned char)send_buff[i]);
    }
    printf("\n");
    #endif

    int sentlen = sendto(ifconfig.socket_id, send_buff, end_idx + header.size, 0, (sockaddr *)&to, sizeof(to));
    if (sentlen == -1) {
      delete[] send_buff;
      throw std::runtime_error("Failed to send a message");
    }

  }
  delete[] send_buff;
}

void WLAN::net_listen(void) const {
  char *recv_msg = new char[ifconfig.mtu];

  struct sockaddr_ll from;
  socklen_t fromlen = sizeof(from);
  for (;;) {
    for (;;) {
      std::memset(recv_msg, 0, ifconfig.mtu);
      if (recvfrom(ifconfig.socket_id, recv_msg, ifconfig.mtu, 0, (struct sockaddr *)&from, &fromlen) == -1) {
        std::cout << "Can not recv msg" << std::endl;
        usleep(10000);
      } else {
        break;
      }
    }

    WLAN_header *wlan_hdr = (WLAN_header *)recv_msg;
    std::string msg = std::string(recv_msg + wlan_hdr->size);
    std::cout << "| dst : " << wlan_hdr->dst.to_string(true) << 
                " | src : " << wlan_hdr->src.to_string(true) << 
                " | " <<  msg << 
                " | data size : " << msg.size() << 
                " | " << std::endl;
  }
  delete[] recv_msg;
}

void WLAN::send_ARP_request(const char *iface, const char *sourceIP, const char *targetIP) {
  int sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_IP);

  struct ifreq ifr {};

  sockfd = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ALL));
  if (sockfd == -1)
    throw std::runtime_error("Socket creation error");

  strncpy(ifr.ifr_name, iface, IFNAMSIZ - 1);
  if (ioctl(sockfd, SIOCGIFHWADDR, &ifr) == -1) {
    close(sockfd);
    throw std::runtime_error("Error getting MAC address");
  }

  WLAN_header ethHeader;
  ARP_scanner::ARP_header arpHeader;

  memcpy(ethHeader.src.addr.data(), "\xff\xff\xff\xff\xff\xff",
         MACAddress::size());
  memcpy(ethHeader.dst.addr.data(), ifr.ifr_hwaddr.sa_data,
         MACAddress::size());
  ethHeader.type = htons(ETHERTYPE_ARP);

  arpHeader.hardwareType = htons(ARPHRD_ETHER);
  arpHeader.protocolType = htons(ETH_P_IP);
  arpHeader.hardwareSize = MACAddress::size();
  arpHeader.protocolSize = IPv4Address::size();
  arpHeader.opCode = htons(ARP_scanner::ARP_REQUEST);

  memcpy(arpHeader.senderMac, ifr.ifr_hwaddr.sa_data, MACAddress::size());
  inet_pton(AF_INET, sourceIP, arpHeader.senderIP);
  inet_pton(AF_INET, targetIP, arpHeader.targetIP);

  char packet[WLAN_header::size + arpHeader.size];
  memcpy(packet, &ethHeader, WLAN_header::size);
  memcpy(packet + WLAN_header::size, &arpHeader, arpHeader.size);

#if 0
  for (std::size_t i = 0, end = WLAN_header::size + arpHeader.size; i < end; ++i) {
    if (i % 14 == 0 && i != 0) printf("\n");
    printf("%02x ", (unsigned char)packet[i]);
  }
  printf("\n");
#endif

  struct sockaddr_ll socket_address;
  memset(&socket_address, 0, sizeof(socket_address));
  socket_address.sll_ifindex = if_nametoindex(iface);
  socket_address.sll_family = AF_PACKET;
  if (sendto(sockfd, packet, sizeof(packet), 0,
             (struct sockaddr *)&socket_address,
             sizeof(socket_address)) == -1) {
    close(sockfd);
    throw std::runtime_error("Error sending ARP request");
  }

  close(sockfd);
}

bool WLAN::parse_ARP_response(const char *buffer) {
  ARP_scanner::ARP_header *arpHeader = (ARP_scanner::ARP_header *)(buffer + WLAN_header::size);

  // if (ntohs(arpHeader->opCode) != ARP_scanner::ARP_REPLY)
  //   return false;

  std::stringstream t_ssf;
  for (std::size_t i = 0, end = MACAddress::size(); i < end; ++i) {
    t_ssf << std::setfill('0') << std::setw(2) << std::right << std::hex
          << (int)arpHeader->senderMac[i];
    t_ssf << ((i + 1 != end) ? ":" : "");
  }
  std::string val = t_ssf.str();
  MACAddress val_addr(val, true);

  std::stringstream t_sss;
  for (std::size_t i = 0, end = IPv4Address::size(); i < end; ++i) {
    t_sss << (int)arpHeader->targetIP[i];
    t_sss << ((i + 1 != end) ? "." : "");
  }
  std::string key = t_sss.str();
  ARP_table[key] = val_addr;

  // std::cout << key << std::endl;

  return true;
}

void WLAN::show_ARP_table(std::ostream &out) {
  for (auto const &pair : ARP_table) {
    out << "{" << pair.first << ": " << pair.second.to_string(true) << "}\n";
  }
}

// refactor this method, please
void WLAN::scan_subnet(void) {
  int fd;
  struct ifreq ifr;

  fd = socket(AF_INET, SOCK_DGRAM, IPPROTO_IP);
  ifr.ifr_addr.sa_family = AF_INET;
  strncpy(ifr.ifr_name, interface.data(), IFNAMSIZ - 1);
  if (ioctl(fd, SIOCGIFNETMASK, &ifr) == -1) {
    close(fd);
    throw std::runtime_error("Error getting subnet mask");
  }
  close(fd);

  fd = socket(AF_INET, SOCK_DGRAM, IPPROTO_IP);
  char subnet_mask[20];
  char sourceIP[20];
  for (std::size_t i = 0, end = sizeof(subnet_mask); i < end; ++i) {
    subnet_mask[i] = 0, sourceIP[i] = 0;
  }
  strcpy(subnet_mask, inet_ntoa(((struct sockaddr_in *)&ifr.ifr_addr)->sin_addr));

  if (ioctl(fd, SIOCGIFADDR, &ifr) == -1) {
    close(fd);
    throw std::runtime_error("Error getting IP address");
  }
  close(fd);

  for (std::size_t i = 0, end = sizeof(sourceIP); i < end; ++i)
    sourceIP[i] = 0;
  strcpy(sourceIP, inet_ntoa(((sockaddr_in *)&ifr.ifr_addr)->sin_addr));

  IPv4Address subnet(subnet_mask), source(sourceIP);
  #if 0
    std::cout << source.to_string(true) << std::endl;
  #endif

  for (std::size_t i = 0, end = IPv4Address::size(); i < end; ++i) {
    source.addr[i] &= subnet.addr[i];
  }

  std::size_t subnet_size = 0;
  for (std::size_t i = 0, end = IPv4Address::size(); i < end; ++i) {
    for (std::size_t j = 0, jend = 8; j < jend; ++j) {
      subnet_size += ((subnet.addr[i] >> j) & 1);
    }
  }
  std::size_t numHosts = 1 << (32 - subnet_size);
  if (numHosts != 0)
    --numHosts;

  char buffer[ETH_FRAME_LEN];
  int sockfd = socket(PF_PACKET, SOCK_RAW, htons(ETH_P_ARP));
  if (sockfd == -1)
    throw std::runtime_error("Socket creation error");


  send_ARP_request(interface.data(), sourceIP, source.to_string().data());
  close(sockfd);

  sockfd = socket(PF_PACKET, SOCK_RAW, htons(ETH_P_ARP));
  // 4 -- max arp request count in network TODO: XENO FIX'i
  for (int i = 0; i < 4; ++i) {
    ssize_t bytesRead = recv(sockfd, buffer, sizeof(buffer), MSG_TRUNC);
    if (bytesRead == -1) {
      close(sockfd);
      throw std::runtime_error("Error receiving ARP response");
    }

    parse_ARP_response(buffer);

  }
  close(sockfd);
}

std::vector<std::string> WLAN::get_all_interfaces(void) {
  std::vector<std::string> result = {};

  struct ifaddrs *addrs;
  getifaddrs(&addrs);

  for (struct ifaddrs *addr = addrs; addr != nullptr; addr = addr->ifa_next) {
    if (addr->ifa_addr && addr->ifa_addr->sa_family == AF_PACKET) {
      std::string t = std::string(addr->ifa_name);
      result.push_back(t);
    }
  }

  freeifaddrs(addrs);

  return result;
}

} // namespace Network
