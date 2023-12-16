#ifndef __KeyGenerator_hh__
#define __KeyGenerator_hh__

#include <stdexcept>
#include <cstdint>
#include <vector>
#include <any>

namespace Crypto {

enum class KeyGenerators {
	BBS_Keygen,
	/* Key generator method types */
};

class IKeyGenerator {
public:
	virtual ~IKeyGenerator() = default; // virtual dtor
	IKeyGenerator(const KeyGenerators generatorType, const std::vector<std::uint64_t> &seed);
	virtual std::uint64_t get_next_key() = 0; // pure virtual method

	[[nodiscard]] static IKeyGenerator *new_keygenerator(const KeyGenerators generatorType, const std::vector<std::uint64_t> &seed);
protected:
	const KeyGenerators generatorType; // type of key generator
	const std::vector<std::uint64_t> &seed; // seed of generator
};

class BBS final: public IKeyGenerator {
public:
	BBS(const std::vector<std::uint64_t>& seed);

	std::uint64_t get_next_key() override;

	~BBS() = default;
private:
    std::uint64_t mod;
    std::uint64_t prev_state;
};

}

#endif
