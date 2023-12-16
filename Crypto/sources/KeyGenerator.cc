#include <KeyGenerator.hh>

namespace Crypto {

IKeyGenerator::IKeyGenerator(const KeyGenerators generatorType, const std::vector<std::uint64_t> &seed) :
	generatorType(generatorType),
	seed(seed) {}

BBS::BBS(const std::vector<std::uint64_t>& seed):
	IKeyGenerator(KeyGenerators::BBS_Keygen, seed) {
		if (seed.size() != 2) {
			throw std::runtime_error("Vector_param incorrect init");
		}
		prev_state = seed[0];
		mod        = seed[1];
}

std::uint64_t BBS::get_next_key() {
	std::uint64_t result_state = 0;
	for (std::size_t i = 0, end = 8 * sizeof(typeof(result_state)); i < end; ++i) {
		prev_state = (prev_state * prev_state) % mod;
		result_state = (result_state << 1) | (prev_state & 1);
	}
	return result_state;
}

IKeyGenerator *IKeyGenerator::new_keygenerator(const KeyGenerators generatorType, const std::vector<std::uint64_t> &seed) {
	switch (generatorType) {
	case KeyGenerators::BBS_Keygen:
		return new BBS(seed);
	default:
		throw std::runtime_error("Unknown KeyGenerator type");
	}
}

}
