#include <Network/WLAN.hh>

int main(void) {
  Network::WLAN wlan("wlan0");
  wlan.ifconfig_info(std::cout);
  std::string recv_msg;
  wlan.recieve(recv_msg);
  std::cout << recv_msg << std::endl;
  return 0;
}