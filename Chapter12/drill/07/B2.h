#ifndef B2_H
#define B2_H

struct B2 {
	virtual void pvf() const = 0;
};

void f(const B2&);
#endif
