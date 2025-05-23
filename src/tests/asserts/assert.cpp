#include "siri-tools.hpp"

int main([[maybe_unused]] int argc, char **argv) {
	siri::tools::assert(argv[1][0] == '1', 
			"Argument did not equal 1.");
	return 0;
}
