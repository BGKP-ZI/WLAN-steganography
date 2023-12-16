#include <HICCUPS.hh>

int main(void) {
    HICCUPS::HICCUPS hiccups("wlan0");

    std::string to_load = "file.png";
    std::vector<std::uint64_t> seed = {2, 997};

    Network::MACAddress addr("69:03:e8:60:a4:b0");

    Crypto::DataLoader cdataloader(Crypto::ChipperT::SimpleXOR, Crypto::KeyGenerators::BBS_Keygen, seed);
    hiccups.HDC3_send(addr, cdataloader, to_load);

    return 0;
}