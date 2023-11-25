#include <WLAN.hh>

namespace Network {

void WLAN::IfConfig::dump(std::ostream &out) const {
  out << "Socket ID : " << socket_id << std::endl;
  out << "Interface Index : " << interface_index << std::endl;
  out << "MAC : " << MAC.to_string(true) << std::endl;
  out << "MTU : " << mtu << std::endl;
}

}