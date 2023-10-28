#ifndef __WLAN_hh__
#define __WLAN_hh__

#include <cstring>
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

#include <Network/Address.hh>

#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <netinet/if_ether.h>
#include <net/if.h>
#include <unistd.h>
#include <sys/ioctl.h>

#include <netpacket/packet.h>

#include <net/ethernet.h>
#include <net/if.h>

#include <arpa/inet.h>

namespace Network {

class WLAN final {
public:
  [[nodiscard]] WLAN(const std::string &interface);

  void setup_interface(void);
  void ifconfig_info(std::ostream &out) const noexcept;

  void probe(const IPv4Address &addr);
  void send(const MACAddress &addr, const std::string &msg) const;
  void recieve(std::string &msg) const;

  WLAN(const WLAN &) = delete;
  WLAN &operator=(const WLAN &) = delete;

  ~WLAN();
private:
  void linux_setup_interface(void);
  void set_toaddr(const MACAddress &addr,
                  struct sockaddr_ll &to) const noexcept;

  struct IfConfig final {
  public:
    std::size_t socket_id = std::size_t(-1);
    std::size_t interface_index = 0;
    MACAddress MAC;
    std::size_t mtu = 0;

    void dump(std::ostream &out) const;
  };

  struct WLAN_header final {
  public:
    MACAddress src;
    MACAddress dest;
    uint16_t type = 0x0139;

    [[nodiscard]] std::size_t size() const;
    WLAN_header(const MACAddress &to_address, const IfConfig &ifconf);
    WLAN_header() {}
    void cp2buff(char *buff) const noexcept;
  };

  struct ARP_scanner final {
    static inline unsigned char ARP_REQUEST = 0x01;
    static inline unsigned char ARP_REPLY   = 0x02;

    #define MAC_ADDR_LENGTH 6
    #define IP_ADDR_LENGTH  4
    #define ETHERNET_HEADER_LENGTH 14

    struct ARP_header final {
      static inline std::size_t size = 28;

      uint16_t hardwareType;
      uint16_t protocolType;
      uint8_t hardwareSize;
      uint8_t protocolSize;
      uint16_t opCode;
      uint8_t senderMac[MAC_ADDR_LENGTH];
      uint8_t senderIP[IP_ADDR_LENGTH];
      uint8_t targetMac[MAC_ADDR_LENGTH];
      uint8_t targetIP[IP_ADDR_LENGTH];
    };

    static void sendArpRequest(const char *iface, const char *targetIp, const char *sourceIP);
    static bool parseArpResponse(const char *buffer);
    static void send_and_parse(const char *iface, const char *targetIp);
  };

  std::string interface;
  IfConfig ifconfig;
  std::unordered_map<std::string, MACAddress> ARP_table;
};

} // namespace Network

#endif