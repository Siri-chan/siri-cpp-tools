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

#include <cassert>
#include <iostream>

#define _SIRI_DEBUG
#include "siri-tools.hpp"

class A {
public:
	siri::tools::RecalculateLazy<int> *computed = new siri::tools::RecalculateLazy<int>(this->recalc());
	int getBase() {
		return base;
	}
	void setBase(int base) {
		this->base = base;
		computed->poison();
	}
private:
	int base = 0;
	std::function<int(void)> recalc() {
		// NOTE: This lambda captures `this` by reference, 
		// and so `this` in the lambda's context will mutate automatically, 
		// when `base` changes.
		auto lambda = [this]() {return base + 1;};
		return lambda;
	}
};

int main(void) {
	auto a = new A();
	std::cout << "Default Base: " << a->getBase() << std::endl;
	std::cout << "Computed Value: " << a->computed->get() << std::endl;
	assert(a->computed->get() == 1);
	a->setBase(10);
	std::cout << "Modified Base: " << a->getBase() << std::endl;
	std::cout << "New Computed Value: " << a->computed->get() << std::endl;
	assert(a->computed->get() == 11);
	return 0;
}
