#ifndef __RawData_hh__
#define __RawData_hh__

#include <cstdint>
#include <string>

namespace Network {

struct RawData final {
    uint8_t  type;          // request/reply data
    uint32_t packet_num;    // number of sended/recieved packet
    uint8_t  is_end;        // is it last packet
    uint8_t name_length;    // length of name
    uint8_t *file_name;     // for saving data format
    uint8_t *data;          // data that sending
    uint32_t crc;           // for checking correct sum of packet

    [[nodiscard]] RawData();
    [[nodiscard]] RawData();

    RawData(const RawData &)  = delete;
    RawData(const RawData &&) = delete;
    RawData &operator=(const RawData &)  = delete;
    RawData &operator=(const RawData &&) = delete;
    ~RawData();

    void set_data(const std::string &);
    void set_name(const std::string &);
    void crc_calc(void);
};

struct CRC4 final {
    uint8_t CRCTable[256];
    const static uint8_t CRC7_POLY = 0x91;

    [[nodiscard]] static uint32_t calc(const std::string &data);
};
// function for calculate crc code

}
#endif