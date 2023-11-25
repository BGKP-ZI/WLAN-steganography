#include <WLAN.hh>

namespace Network {

#ifdef WINDOWS_SYSTEM
WLAN::WLAN(const std::string &interface) : interface(interface) {
  setup_interface();
}

void WLAN::setup_interface(void) {
}

WLAN::~WLAN() {
}

void WLAN::ifconfig_info(std::ostream &out) const noexcept {
  ifconfig.dump(out);
}

void WLAN::set_toaddr(const MACAddress &addr, struct sockaddr_ll &to) const noexcept {
}

void WLAN::probe(const IPv4Address &addr) {
}

void WLAN::send(const MACAddress &addr, const std::string &msg) const {
}

void WLAN::recieve(std::string &msg) const {
}

void WLAN::send_ARP_request(const char *iface, const char *targetIP) {
}

void WLAN::send_and_parse(const char *iface, const char *targetIp) {
}

bool WLAN::parse_ARP_response(const char *buffer){
  return false;
}

void WLAN::show_ARP_table(std::ostream &out) {
}

void WLAN::scan_subnet(void) {
}

std::vector<std::string> WLAN::get_all_interfaces(void) {
  return std::vector<std::string>();
}
#endif

} // namespace Network
