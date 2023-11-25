#include <WLAN.hh>

namespace Network {

WLAN::WLAN_header::WLAN_header() {
}

WLAN::WLAN_header::WLAN_header(const MACAddress &to_addr,
                               const IfConfig &ifconfig) {
  std::memmove(dest.addr.data(), to_addr.addr.data(), dest.size());
  std::memmove(src.addr.data(), ifconfig.MAC.addr.data(), src.size());
}

void WLAN::WLAN_header::cp2buff(char *buff) const noexcept {
  std::memmove(buff, dest.addr.data(), dest.size());
  std::memmove(buff + dest.size(), src.addr.data(), dest.size());
  std::memmove(buff + 2 * dest.size(), &type, sizeof(type));
}

}
