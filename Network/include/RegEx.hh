#ifndef __RegEx_hh__
#define __RegEx_hh__

namespace Network {

struct RegEx final {
  static inline char IPv4_regex[] = "(([0-9]|[1-9][0-9]|1[0-9][0-9]|2[0-4][0-9]"
                                    "|25[0-5])\\.){3}([0-9]|[1-9][0-"
                                    "9]|1[0-9][0-9]|2[0-4][0-9]|25[0-5])";
  static inline char MAC_regex[] =
      "^([0-9A-Fa-f]{2}[:-]){5}([0-9A-Fa-f]{2})|([0-9a-"
      "fA-F]{4}\\.[0-9a-fA-F]{4}\\.[0-9a-fA-F]{4})$";
};

} // namespace Network
#endif