#include <iostream>

#include "siri-tools.hpp"

int main(int argc, char **argv) {
	std::cout << "G++ and Meson are playing nice woohoo!" << std::endl << "Arguments are:" << std::endl;
	for (int i = 0; i < argc; i++) {
		std::cout << argv[i] << std::endl;
	}
	return siri::tools::sanity_check();
}
