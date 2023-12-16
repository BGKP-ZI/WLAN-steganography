#include <DataLoader.hh>

namespace Crypto {

DataLoader::DataLoader(const ChipperT c_type, const KeyGenerators g_type, const std::vector<std::uint64_t> &seed) : 
    encoder(IChipper::new_chipper(g_type, c_type, seed)) {}

DataLoader::~DataLoader() {
    delete encoder;
}

std::string DataLoader::load(const std::string &path) {
    std::ifstream t(path.data());
    std::stringstream buffer;
    buffer << t.rdbuf();
    return buffer.str();
}

void DataLoader::save(const std::string &data, const std::string &path) {
    std::ofstream binFile (path, std::ios::out | std::ios::binary);
    if (binFile.is_open()) {
        binFile.write(data.data(), data.size());
        binFile.close();
    } else {
        throw std::runtime_error("Can\'t open file\n");
    }
}

std::string DataLoader::chipper_text(const std::string &ctext) {
    return encoder->chipper(ctext);
}

std::string DataLoader::dechipper_text(const std::string &etext) {
    return encoder->dechipper(etext);
}

}