#include <KeyGenerator.hh>
#include <iostream>

int main() {
	try {
		Crypto::BBS noize(Crypto::KeyGenerators::BBS_Keygen, {(unsigned)2, (unsigned)997});
		for (int i = 0; i < 10; ++i) {
			printf("Next generated key is : 0x%08x\n", noize.get_next_key());
		}
	} catch (const std::exception &e) {
		std::cout << "Except in ctor" << std::endl;
		std::cout << e.what() << std::endl;
	}
	return 0;

}
