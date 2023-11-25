#include <KeyGenerator.hh>

namespace Crypto {

IKeyGenerator::IKeyGenerator(const KeyGenerators generatorType, const std::vector<std::any> &seed) :
	generatorType(generatorType),
	seed(seed) {}

BBS::BBS(const KeyGenerators generatorType, const std::vector<std::any>& seed):
	IKeyGenerator(generatorType, seed) {
		if (seed.size() != 2) {
			throw std::runtime_error("Vector_param uncorrect init");
		}
		prev_state = std::any_cast<unsigned>(seed[0]);
		mod        = std::any_cast<unsigned>(seed[1]);
}

unsigned BBS::get_next_key() {
	unsigned result_state = 0;
	for (std::size_t i = 0, end = 8 * sizeof(unsigned); i < end; ++i) {
		prev_state = (prev_state * prev_state) % mod;
		result_state = (result_state << 1) | (prev_state & 1);
	}
	return result_state;
}

}
