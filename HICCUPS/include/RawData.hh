#ifndef __RawData_hh__
#define __RawData_hh__

#include <cstdint>
#include <string>

namespace HICCUPS {

struct RawData final {
    std::uint8_t  type;         // request/reply data
    std::uint32_t packet_num;   // number of sended/recieved packet
    std::uint8_t  is_end;       // is it last packet
    std::uint8_t name_length;   // length of name
    std::string file_name;      // for saving data format
    std::string data;           // data that sending
    std::uint32_t crc;          // for checking correct sum of packet

    [[nodiscard]] RawData();

    RawData(const RawData &)  = delete;
    RawData(RawData &&);
    RawData &operator=(const RawData &) = delete;
    RawData &operator=(RawData &&);

    void swap(RawData &);

    void set_data(const std::string &);
    void set_name(const std::string &);
    void crc_calc(void);
    [[nodiscard]] std::string to_string() const;
};

struct CRC4 final {
    const static std::uint8_t CRC7_POLY = 0x91;

    // static std::uint8_t CRCTable[256];

    // [[nodiscard]] static std::uint8_t getCRCForByte(std::uint8_t val);
    // static void buildCRCTable();
    [[nodiscard]] static uint32_t calc(const std::string &data);
};

}

#endif