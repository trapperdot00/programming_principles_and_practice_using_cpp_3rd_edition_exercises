#ifndef MONEY_H
#define MONEY_H

#include <iostream>
#include <cmath>
#include <stdexcept>
#include <array>
#include <string_view>

enum class Currency {
	USD, EUR, HUF, DKK, CHF
};

int to_int(Currency);
Currency int_to_currency(int);
auto currency_denom_table() -> std::array<std::string_view, 5>;
std::string_view to_denom(Currency);
int find_in_denom_table(std::string_view);
bool in_range(Currency);
double conversion_rate(Currency, Currency);

template <typename T, typename T2>
T narrow(const T2& t) {
	T ret = t;
	if (ret != t)
		throw std::runtime_error{"narrow error"};
	return ret;
}

class Money {
public:
	Money() {}
	Money(double d, Currency cc) : a{narrow<long int>(d*100)}, c{cc} {}
	Money& operator=(double d) {
		a = narrow<long int>(d*100);
		return *this;
	}

	long int amount() const { return a; }
	Currency currency() const { return c; }

	// Change currency to another one,
	// without changing the amount
	void set_currency(Currency cc) {
		if (!in_range(cc))
			throw std::runtime_error{"Currency out of range"};
		c = cc;
	}

	Money& operator+=(const Money&);
	Money& operator-=(const Money&);
private:
	// Round using the 4/5 rule:
	// digit of tenth of a cent determines rounding:
	//  - digits 0-4 are rounded down,
	//  - digits 5-9 are rounded up
	long int round(double) const;

	long int a = 0;
	Currency c;
};

Money operator+(const Money&, const Money&);
Money operator-(const Money&, const Money&);

std::istream& operator>>(std::istream&, Money&);
// Print using $123.45 form
std::ostream& operator<<(std::ostream&, const Money&);

#endif
