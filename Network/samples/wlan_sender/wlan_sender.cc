#include <WLAN.hh>

#include <sstream>
#include <string>
#include <fstream>

int main(void) {
  Network::WLAN wlan("wlan0");
  wlan.ifconfig_info(std::cout);
  Network::MACAddress addr("69:03:e8:60:a4:b0", true);
  std::ifstream t("alice.txt");
  std::stringstream buffer;
  buffer << t.rdbuf();
  // std::string message = "";
  
  wlan.send(addr, buffer.str().data());
  return 0;
}
