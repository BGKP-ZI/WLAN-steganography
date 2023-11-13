#ifndef __WLAN_hh__
#define __WLAN_hh__

#include <cstring>
#include <iomanip>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

#include <Network/Address.hh>

#include <net/if.h>
#include <netinet/if_ether.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <unistd.h>

#include <netpacket/packet.h>

#include <net/ethernet.h>
#include <net/if.h>

#include <arpa/inet.h>
#include <ifaddrs.h>

namespace Network {

class WLAN final {
public:
  [[nodiscard]] WLAN(const std::string &interface);

  void setup_interface(void);
  void ifconfig_info(std::ostream &out) const noexcept;

  [[nodiscard]] static std::vector<std::string> get_all_interfaces(void);
  void probe(const IPv4Address &addr);
  void send(const MACAddress &addr, const std::string &msg) const;
  void recieve(std::string &msg) const;
  void scan_subnet(void);

  void show_ARP_table(std::ostream &out);

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

    [[nodiscard]] constexpr static inline std::size_t size();
    WLAN_header(const MACAddress &to_address, const IfConfig &ifconf);
    WLAN_header() {}
    void cp2buff(char *buff) const noexcept;
  };

  struct ARP_scanner final {
    constexpr static inline unsigned char ARP_REQUEST = 0x01;
    constexpr static inline unsigned char ARP_REPLY = 0x02;

    struct ARP_header final {
      constexpr static inline std::size_t size = 28;

      uint16_t hardwareType;
      uint16_t protocolType;
      uint8_t hardwareSize;
      uint8_t protocolSize;
      uint16_t opCode;
      uint8_t senderMac[MACAddress::size()];
      uint8_t senderIP[IPv4Address::size()];
      uint8_t targetMac[MACAddress::size()];
      uint8_t targetIP[IPv4Address::size()];
    };
  };
  void send_ARP_request(const char *iface, const char *targetIp);
  bool parse_ARP_response(const char *buffer);
  void send_and_parse(const char *iface, const char *targetIp);

  std::string interface;
  IfConfig ifconfig;
  std::unordered_map<std::string, MACAddress> ARP_table = {};
};

} // namespace Network

#endif