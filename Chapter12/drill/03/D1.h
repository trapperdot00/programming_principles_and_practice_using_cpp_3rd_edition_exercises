#ifndef D1_H
#define D1_H

#include "B1.h"

struct D1 : public B1 {
	void vf() const override {
		std::cout << "D1::vf()\n";
	}
};

#endif
