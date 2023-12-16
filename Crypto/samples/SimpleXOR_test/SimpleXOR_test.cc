#include <Chippers.hh>

#include <iostream>

using namespace Crypto;

int main(void) {
    std::string text = "Hello World! Hello Mr Putin!";
    std::cout << "Raw text: \"" << text << "\" with length = "  << text.size() << std::endl;

    std::vector<std::uint64_t> seed = {2, 997};

    SimpleXOR c(KeyGenerators::BBS_Keygen, seed);
    SimpleXOR d(KeyGenerators::BBS_Keygen, seed);

    std::string ctext = c.  chipper( text);
    std::string etext = d.dechipper(ctext);

    std::cout << "Chippered text : " << std::endl << "\t" ;
    for (std::size_t i = 0, i_end = ctext.size(); i < i_end; ++i) {
        printf("%c", ctext[i]);
    }
    printf("\n");

    std::cout << "Encrypted text : " << std::endl << "\t" ;
    for (std::size_t i = 0, i_end = etext.size(); i < i_end; ++i) {
        printf("%c", etext[i]);
    }
    printf("\n");

    return 0;
}