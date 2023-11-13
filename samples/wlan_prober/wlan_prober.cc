#include <Network/WLAN.hh>

int main(void) {

  std::vector<std::string> interfaces = Network::WLAN::get_all_interfaces();
  std::cout << "List of all interfaces" << std::endl;
  for (std::size_t i = 0; i < interfaces.size(); ++i) {
    std::cout << interfaces[i] << std::endl;
  }
  std::cout << "Choosen interface : " << interfaces[interfaces.size() - 1]
            << std::endl;
  Network::WLAN wlan(interfaces[interfaces.size() - 1]);
  wlan.scan_subnet();
  wlan.show_ARP_table(std::cout);

  return 0;
}