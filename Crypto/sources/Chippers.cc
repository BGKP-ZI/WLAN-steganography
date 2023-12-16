#include <Chippers.hh>

namespace Crypto {

IChipper::~IChipper() {
    delete key_gen;
}

IChipper::IChipper(const KeyGenerators gen_type, const std::vector<std::uint64_t> &seed) :
    key_gen(IKeyGenerator::new_keygenerator(gen_type, seed)) {}

IChipper *IChipper::new_chipper(const KeyGenerators gen_type, const ChipperT chipper_type, const std::vector<std::uint64_t> &seed) {
    switch (chipper_type) {
        case ChipperT::SimpleXOR:
            return new SimpleXOR(gen_type, seed);
        default:
            throw std::runtime_error("Unknown chipper type");
    }
}

SimpleXOR::SimpleXOR(const KeyGenerators gen_type, const std::vector<std::uint64_t> &seed) : 
    IChipper(gen_type, seed) {}

std::string SimpleXOR::chipper(const std::string &ctext) {
    std::string result;
    result.resize(ctext.size());

    for (std::size_t i = 0, i_end = result.size(), step = sizeof(std::uint64_t)/sizeof(char); i < i_end; i += step) {
        std::uint64_t key = key_gen->get_next_key();
        for (std::size_t j = 0, j_end = std::min(step, i_end - i); j < j_end; ++j) {
            result[i+j] = ctext[i+j] ^ ((key >> 8*j) & 0xff);
        }
    }

    return result;
}

std::string SimpleXOR::dechipper(const std::string &etext) {
    std::string result;
    result.resize(etext.size());

    for (std::size_t i = 0, i_end = result.size(), step = sizeof(std::uint64_t)/sizeof(char); i < i_end; i += step) {
        std::uint64_t key = key_gen->get_next_key();
        for (std::size_t j = 0, j_end = std::min(step, i_end - i); j < j_end; ++j) {
            result[i+j] = etext[i+j] ^ ((key >> 8*j) & 0xff);
        }
    }

    return result;
}

}