#include "Money.h"

long int Money::round(double d) const {
	long int value = d * 100;
	// To check digit of tenth of a cent
	long int helper = d * 1000;
	if (helper % 10 > 4)
		++value;
	return value;
}

std::istream& operator>>(std::istream& is, Money& rhs) {
	double val = 0.0;
	if (is >> val)
		rhs = val;
	return is;
}

std::ostream& operator<<(std::ostream& os, const Money& rhs) {
	long int value = rhs.amount();
	return os << '$' << value / 100 << '.' << std::abs(value % 100);
}
