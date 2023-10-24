#ifndef __IPv4Address_hh__

#define __IPv4Address_hh__
#define IPv4_ADDRESS_SIZE 4

#include <cstdint>
#include <iostream>
#include <regex>
#include <string>

namespace Network {

struct IPv4Address final {
public:
  [[nodiscard]] IPv4Address();
  [[nodiscard]] IPv4Address(const std::string &);
  [[nodiscard]] IPv4Address(const IPv4Address &) noexcept;
  IPv4Address &operator=(const IPv4Address &) noexcept;

  [[nodiscard]] std::string to_string() const noexcept;

  static const std::regex address_regex;

private:
  unsigned char addr[IPv4_ADDRESS_SIZE];
  [[nodiscard]] static bool IsValid(const std::string &str) noexcept;
};

}

std::ostream &operator<<(std::ostream &, const Network::IPv4Address &);
std::istream &operator>>(std::istream &, Network::IPv4Address &);

#endif