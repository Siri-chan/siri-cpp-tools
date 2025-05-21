/*
This file is part of siri::tools.

siri::tools is free software: 
you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License 
as published by the Free Software Foundation, either version 3 of the License, 
or (at your option) any later version.

siri::tools is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; 
without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. 
See the GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License along with siri::tools. 
If not, see <https://www.gnu.org/licenses/>. 
*/

#include <iostream>

#include "siri-tools.hpp"

int main(int argc, char **argv) {
	std::cout << "This test compiled and linked properly!" << std::endl << "Arguments are:" << std::endl;
	for (int i = 0; i < argc; i++) {
		std::cout << argv[i] << std::endl;
	}
	return siri::tools::sanity_check();
}
