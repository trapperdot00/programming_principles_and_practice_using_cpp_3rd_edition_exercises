#ifndef MONEY_H
#define MONEY_H

#include <iostream>
#include <cmath>

class Money {
public:
	Money() {}
	Money(double d) : a{round(d)} {}
	Money& operator=(double d) {
		a = round(d);
		return *this;
	}

	long int amount() const { return a; }
private:
	// Round using the 4/5 rule:
	// digit of tenth of a cent determines rounding:
	//  - digits 0-4 are rounded down,
	//  - digits 5-9 are rounded up
	long int round(double) const;

	long int a = 0;
};

std::istream& operator>>(std::istream&, Money&);
// Print using $123.45 form
std::ostream& operator<<(std::ostream&, const Money&);

#endif
