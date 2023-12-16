#include <DataLoader.hh>

using namespace Crypto;

int main(void) {
    std::string to_load = "file.png";
    std::string to_save = "saved.png";

    std::string data = DataLoader::load(to_load);

    std::vector<std::uint64_t> seed = {2, 997};
    DataLoader cdataloader(ChipperT::SimpleXOR, KeyGenerators::BBS_Keygen, seed);
    DataLoader ddataloader(ChipperT::SimpleXOR, KeyGenerators::BBS_Keygen, seed);
    
    std::string ctext = cdataloader.chipper_text(data);
    DataLoader::save(ctext, "encrypted_" + to_save);

    std::string efile = DataLoader::load("encrypted_" + to_save);
    std::string etext = ddataloader.dechipper_text(efile);

    DataLoader::save(etext, to_save);

    return 0;
}