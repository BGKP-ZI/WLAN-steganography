#include <WLAN.hh>

int main(void) {
  Network::WLAN wlan("wlan0");
  wlan.ifconfig_info(std::cout);
  Network::MACAddress addr("69:03:e8:60:a4:b0", true);
	std::string message = "";
	for (std::size_t i = 0; i < 1520; ++i) {
		message += "a";
	}
	wlan.send(addr, message.data());
  return 0;
}
