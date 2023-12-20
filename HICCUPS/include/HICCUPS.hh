#ifndef __HICCUPS_hh__
#define __HICCUPS_hh__

#include <WLAN.hh>
#include <DataLoader.hh>
#include <RawData.hh>

namespace HICCUPS {

class HICCUPS : public Network::WLAN {
public:
    [[nodiscard]] HICCUPS(const std::string &interface);

    void HDC2_send(const Network::MACAddress &, Crypto::DataLoader &, const std::string &);
    void HDC3_send(const Network::MACAddress &, Crypto::DataLoader &, const std::string &);

    void HDC2_recv(const Network::MACAddress &, Crypto::DataLoader &, const std::string &);
    void HDC3_recv(const Network::MACAddress &, Crypto::DataLoader &, const std::string &);
};

}

#endif