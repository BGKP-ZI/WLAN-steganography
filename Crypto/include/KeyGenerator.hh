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
	IKeyGenerator(const KeyGenerators generatorType, const std::vector<std::any> &seed);
	virtual unsigned get_next_key() = 0; // pure virtual method
protected:
	const KeyGenerators generatorType; // type of key generator
	const std::vector<std::any> &seed; // seed of generator
};

class BBS final: public IKeyGenerator {
public:
	BBS(const KeyGenerators generatorType, const std::vector<std::any>& seed);

	unsigned get_next_key() override;

	~BBS() = default;
private:
    unsigned mod;
    unsigned prev_state;
};

}

#endif
