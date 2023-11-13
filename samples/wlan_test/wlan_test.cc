#include <Network/WLAN.hh>

int main(void) {
  Network::WLAN wlan("eth0");
  wlan.ifconfig_info(std::cout);
  return 0;
}