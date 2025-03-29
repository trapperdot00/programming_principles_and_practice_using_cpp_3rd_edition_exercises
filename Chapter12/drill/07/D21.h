#ifndef D21_H
#define D21_H

#include "B2.h"

#include <iostream>
#include <string>

struct D21 : public B2 {
	void pvf() const override {
		std::cout << value << '\n';
	}
	std::string value;
};

#endif
