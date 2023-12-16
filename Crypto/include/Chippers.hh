#ifndef __Chippers_hh__
#define __Chippers_hh__

#include <KeyGenerator.hh>

#include <vector>
#include <string>

namespace Crypto {

enum class ChipperT {
	SimpleXOR,
	/* Chipper types  */
};

struct IChipper {
public:
	IChipper(const KeyGenerators gen_type, const std::vector<std::uint64_t> &seed); // base ctor
	IChipper(const IChipper &)  = delete;
	IChipper(const IChipper &&) = delete;
	IChipper &operator=(const IChipper &)  = delete;
	IChipper &operator=(const IChipper &&) = delete;
	virtual ~IChipper(); //virt dtor

	virtual std::string   chipper(const std::string &etext) = 0; // pure virt func
	virtual std::string dechipper(const std::string &ctext) = 0; // pure virt func
	
	[[nodiscard]] static IChipper *new_chipper(const KeyGenerators gen_type, const ChipperT chipper_type, const std::vector<std::uint64_t> &seed);
protected:
	IKeyGenerator *key_gen;
};

struct SimpleXOR final: IChipper {
public:
	SimpleXOR(const KeyGenerators gen_type, const std::vector<std::uint64_t> &seed);
	[[nodiscard]] std::string dechipper(const std::string &etext) override;
	[[nodiscard]] std::string   chipper(const std::string &ctext) override;
};


}

#endif
