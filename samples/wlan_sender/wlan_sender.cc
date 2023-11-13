#include <Network/WLAN.hh>

int main(void) {
  Network::WLAN wlan("wlan0");
  wlan.ifconfig_info(std::cout);
  Network::MACAddress addr("ff:ff:ff:ff:ff:ff", true);
  wlan.send(addr, "Hello recver!");
  return 0;
}