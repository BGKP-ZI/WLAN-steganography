#include <Network/Address.hh>
#include <Network/WLAN.hh>

int main(void) {
  Network::WLAN wlan("wlan0");
  wlan.ifconfig_info(std::cout);
  // Network::MACAddress addr("ff:ff:ff:ff:ff:ff", true);
  Network::IPv4Address addr("192.168.0.111");
  std::cout << addr.to_string() << std::endl;
  // wlan.send(addr, "Hello recver!");
  wlan.probe(addr);
  return 0;
}