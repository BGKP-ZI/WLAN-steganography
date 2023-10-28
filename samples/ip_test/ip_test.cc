#include <iostream>

#include <Network/Address.hh>

using namespace Network;

int main() {
  try {
    IPv4Address a_1("192.168.51.130");
    std::cout << "I can create address : " << a_1.to_string() << std::endl;
    IPv4Address a_2("273.255.255.255");
    std::cout << "I can create second address" << std::endl;
  } catch (const std::exception &exc) {
    std::cout << exc.what() << std::endl;
  }
  try {
    IPv4Address a_3;
    std::cout << "Please, write address: ";
    std::cin >> a_3;
    std::cout << "Readed address: " << a_3 << std::endl;
  } catch (const std::exception &exc) {
    std::cout << exc.what() << std::endl;
  }
  std::cout << "Now let\'s try MAC addresses" << std::endl;
  try {
    MACAddress mac_1("12:34:56:78:9a:bc", true);
    std::cout << "I can create mac address : " << mac_1.to_string(true)
              << std::endl;
    MACAddress mac_2("af:fe:13");
  } catch (const std::exception &exc) {
    std::cout << exc.what() << std::endl;
  }
  return 0;
}