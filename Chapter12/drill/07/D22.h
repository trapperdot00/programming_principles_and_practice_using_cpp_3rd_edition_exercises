#ifndef D22_H
#define D22_H

#include "B2.h"

#include <iostream>

struct D22 : public B2 {
	void pvf() const override {
		std::cout << value << '\n';
	}
	int value;
};

#endif
