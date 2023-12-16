#ifndef __DataLoader_hh__
#define __DataLoader_hh__

#include <Chippers.hh>

#include <iostream>
#include <vector>
#include <cstdint>
#include <sstream> 
#include <fstream>

namespace Crypto {

struct DataLoader final {
public:
	DataLoader(const ChipperT c_type, const KeyGenerators g_type, const std::vector<std::uint64_t> &seed); // ctor
	
	[[nodiscard]] std::string    chipper_text(const std::string &ctext);
	[[nodiscard]] std::string  dechipper_text(const std::string &etext);
	
	static void save(const std::string &data, const std::string &path);
	[[nodiscard]] static std::string load(const std::string &path);

	~DataLoader(); //dtor
private:
	IChipper *encoder;
};

}

#endif
