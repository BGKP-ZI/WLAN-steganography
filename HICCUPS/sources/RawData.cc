#include <RawData.hh>
#include <iostream>

namespace HICCUPS {

// std::uint8_t CRC4::getCRCForByte(std::uint8_t val) {
//   for (std::uint8_t j = 0; j < 8; ++j) {
//     if (val & 1) val ^= CRC7_POLY;
//     val >>= 1;
//   }
 
//   return val;
// }

// void CRC4::buildCRCTable() { 
//   for (std::size_t i = 0; i < 256; ++i) {
//     CRCTable[i] = getCRCForByte(i);
//   }
// }

std::uint32_t CRC4::calc(const std::string &data) {
  //buildCRCTable(); // TODO: not good for calc optim
  std::uint32_t i, j, crc = 0;
 
  for (i = 0; i < data.size(); ++i) {
    crc ^= data[i];
    for (j = 0; j < 8; ++j) {
      if (crc & 1)
        crc ^= CRC7_POLY;
      crc >>= 1;
    }
  }
  return crc;
}

RawData::RawData() {}

void RawData::swap(RawData &other) {
    std::swap(type, other.type);
    std::swap(packet_num, other.packet_num);
    std::swap(is_end, other.is_end);
    std::swap(name_length, other.name_length);
    std::swap(file_name, other.file_name);
    std::swap(data, other.data);
    std::swap(crc, other.crc);
}

RawData::RawData(RawData &&other) {
    swap(other);
}

RawData &RawData::operator=(RawData &&other) {
    swap(other);
    return *this;
}

void RawData::set_data(const std::string &new_data) {
    for (std::size_t i = 0; i < data.size(); ++i) 
        data[i] = 0;
    data.resize(new_data.size());
    for (std::size_t i = 0, i_end = new_data.size(); i < i_end; ++i)
        data[i] = new_data[i];
}

void RawData::set_name(const std::string &name) {
    for (std::size_t i = 0; i < file_name.size(); ++i)
        file_name[i] = 0;
    file_name.resize(name.size());
    name_length = name.size();
    for (std::size_t i = 0, i_end = name.size(); i < i_end; ++i)
        file_name[i] = name[i];
}

std::string RawData::to_string() const {
    std::string result = "";
    result.resize(data.size() + file_name.size() + 11);

    result[0] = type;
    *((std::uint32_t *)(result.data() + 1)) = packet_num;
    result[5] = is_end;
    result[6] = name_length;
    for (std::size_t i = 0, i_end = file_name.size(), offset = 7; i < i_end; ++i)
        result[offset + i] = file_name[i];
    for (std::size_t i = 0, i_end = data.size(), offset = 7 + file_name.size(); i < i_end; ++i) 
        result[offset + i] = data[i];
    *((std::uint32_t *)(result.data() + 7 + data.size() + file_name.size())) = packet_num;

    return result;
}

void RawData::crc_calc() {
    std::string temp = "";
    std::string d_str = to_string();
    temp.resize(d_str.size() - 4);
    for (std::size_t i = 0, i_end = d_str.size() - 4; i < i_end; ++i) {
        temp[i] = d_str[i];
    }
    crc = CRC4::calc(temp);
}

}
