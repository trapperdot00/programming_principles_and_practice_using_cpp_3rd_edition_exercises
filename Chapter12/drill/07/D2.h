#ifndef D2_H
#define D2_H

#include "D1.h"

struct D2 : public D1 {
	void pvf() const override {
		std::cout << "D2::pvf()\n";
	}
};

#endif
