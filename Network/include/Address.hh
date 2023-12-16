#ifndef __Address_hh__
#define __Address_hh__

#include <RegEx.hh>

#include <array>
#include <cstring>
#include <iostream>
#include <regex>

namespace Network {

template <std::size_t N, const char *REGEX> class Address final {
public:
  [[nodiscard]] Address(void) {
    for (std::size_t i = 0; i < N; ++i)
      addr[i] = 0;
  }

  [[nodiscard]] constexpr static inline std::size_t size(void) { return N; }

  [[nodiscard]] Address(const std::string &str, const bool isHex = false) {
    std::regex regex{REGEX};
    if (!std::regex_match(str, regex))
      throw std::runtime_error("Not valid address: " + str);

    char point;
    unsigned int temp;
    // TODO: think how to correctly get address using regexp
    // (for example IPv6 address ff::01) or MAC address)
    std::stringstream ss_temp(str);
    for (std::size_t i = N; i > 0; --i) {
      if (!isHex) {
        ss_temp >> temp >> point;
        addr[i - 1] = temp;
      } else {
        ss_temp >> std::hex >> temp >> point;
        addr[i - 1] = temp;
      }
    }
  }

  [[nodiscard]] Address(const Address &other) noexcept {
    for (std::size_t i = 0; i < N; ++i)
      addr[i] = other.addr[i];
  }

  Address &operator=(const Address &other) noexcept {
    for (std::size_t i = 0; i < N; ++i)
      addr[i] = other.addr[i];
    return *this;
  }

  [[nodiscard]] std::string to_string(const bool isHex = false) const noexcept {
    if (!isHex) {
      std::string result = "";
      for (std::size_t i = N - 1; i > 0; --i) {
        result += (std::to_string((unsigned int)(addr[i])) + ".");
      }
      return result + std::to_string((unsigned int)(addr[0]));
    } else {
      char result[3 * N] = "";
      for (std::size_t i = N - 1; i > 0; --i) {
        sprintf(result + std::strlen(result), "%02x.", (unsigned char)addr[i]);
      }
      sprintf(result + std::strlen(result), "%02x", addr[0]);
      return std::string(result);
    }
  }

  std::array<unsigned char, N> addr;
};

#define IPv4Address Address<4, Network::RegEx::IPv4_regex>
#define MACAddress Address<6, Network::RegEx::MAC_regex>

} // namespace Network

template <std::size_t N, const char *REGEX>
std::ostream &operator<<(std::ostream &out,
                         const Network::Address<N, REGEX> &address) {
  out << address.to_string();
  return out;
}

template <std::size_t N, const char *REGEX>
std::istream &operator>>(std::istream &in,
                         Network::Address<N, REGEX> &address) {
  std::string temp;
  in >> temp;
  address = Network::Address<N, REGEX>(temp);
  return in;
}

#endif
