#include <cassert>
#include <iostream>

#define _DEBUG
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
