#ifndef B1_H
#define B1_H

#include <iostream>

struct B1 {
	virtual void vf() const {
		std::cout << "B1::vf()\n";
	}
	void f() const {
		std::cout << "B1::f()\n";
	}
};

#endif
