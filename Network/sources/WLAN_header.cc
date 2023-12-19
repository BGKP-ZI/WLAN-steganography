#include <WLAN.hh>

namespace Network {

WLAN::WLAN_header::WLAN_header() {
}

WLAN::WLAN_header::WLAN_header(const MACAddress &to_addr,
                               const IfConfig &ifconfig) {
  std::memmove(dst.addr.data(),      to_addr.addr.data(), MACAddress::size());
  std::memmove(src.addr.data(), ifconfig.MAC.addr.data(), MACAddress::size());
}

void WLAN::WLAN_header::cp2buff(char *buff) const noexcept {
  std::memmove(buff + 0 * MACAddress::size(), dst.addr.data(), MACAddress::size());
  std::memmove(buff + 1 * MACAddress::size(), src.addr.data(), MACAddress::size());
  std::memmove(buff + 2 * MACAddress::size(), &type, sizeof(type));
}

}
