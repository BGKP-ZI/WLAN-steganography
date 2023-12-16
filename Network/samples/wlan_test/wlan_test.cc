#include <WLAN.hh>

int main(void) {
  Network::WLAN wlan("wlan0");
  wlan.ifconfig_info(std::cout);
  return 0;
}
