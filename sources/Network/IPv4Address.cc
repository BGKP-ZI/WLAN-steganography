#include <Network/IPv4Address.hh>

namespace Network {

const std::regex IPv4Address::address_regex =
    std::regex("(([0-9]|[1-9][0-9]|1[0-9][0-9]|2[0-4][0-9]|25[0-5])\\.){3}([0-"
               "9]|[1-9][0-9]|1[0-9][0-9]|2[0-4][0-9]|25[0-5])");

inline bool IPv4Address::IsValid(const std::string &str) noexcept {
  return std::regex_match(str, IPv4Address::address_regex);
}

IPv4Address::IPv4Address() : addr() {
  for (std::size_t i = 0, end = sizeof(addr); i < end; ++i)
    addr[i] = 0;
}

IPv4Address::IPv4Address(const IPv4Address &other) noexcept {
  for (std::size_t i = 0, end = sizeof(addr); i < end; ++i) {
    addr[i] = other.addr[i];
  }
}

IPv4Address &IPv4Address::operator=(const IPv4Address &other) noexcept {
  for (std::size_t i = 0, end = sizeof(addr); i < end; ++i) {
    addr[i] = other.addr[i];
  }
  return *this;
}

IPv4Address::IPv4Address(const std::string &str) {
  char point;
  unsigned int temp;
  std::stringstream ss_temp(str);

  if (!IsValid(str))
    throw std::runtime_error("Not valid IPv4 address: " + str);
  for (std::size_t i = sizeof(addr); i > 0; --i) {
    ss_temp >> temp >> point;
    addr[i - 1] = temp;
  }
}

std::string IPv4Address::to_string() const noexcept {
  std::string result = "";
  for (size_t i = sizeof(addr) - 1; i > 0; --i) {
    result += (std::to_string((unsigned int)(addr[i])) + ".");
  }
  return result + std::to_string((unsigned int)(addr[0]));
}


} // namespace Network

std::ostream &operator<<(std::ostream &out, const Network::IPv4Address &address) {
  out << address.to_string();
  return out;
}

std::istream &operator>>(std::istream &in, Network::IPv4Address &address) {
  std::string temp;
  in >> temp;
  address = Network::IPv4Address(temp);
  return in;
}