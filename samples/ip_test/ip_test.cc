#include <iostream>

#include <Network/IPv4Address.hh>

int main() {
  try {
    Network::IPv4Address a_1("192.168.51.130");
    std::cout << "I can create address : " << a_1.to_string() << std::endl;

    Network::IPv4Address a_2("273.255.255.255");
    std::cout << "I can create second address" << std::endl;
  } catch (const std::exception &exc) {
    std::cout << exc.what() << std::endl;
  }
  try {
    Network::IPv4Address a_3;
    std::cout << "Please, write address: " ;
    std::cin >> a_3;
    std::cout << "Readed address: " << a_3 << std::endl;
  } catch (const std::exception &exc) {
    std::cout << exc.what() << std::endl;
  }
  return 0;
}