#include "Money.h"

int to_int(Currency c) {
	return static_cast<int>(c);
}

Currency int_to_currency(int i) {
	if (i < to_int(Currency::USD) || i > to_int(Currency::CHF))
		throw std::runtime_error{"Currency out of range"};
	return Currency{i};
}

auto currency_denom_table() -> std::array<std::string_view, 5> {
	constexpr static std::array<std::string_view, 5> denom_tbl = {
		"USD", "EUR", "HUF", "DKK", "CHF"
	};
	return denom_tbl;
}

std::string_view to_denom(Currency c) {
	if (!in_range(c))
		throw std::runtime_error{"Currency out of range"};
	return currency_denom_table()[to_int(c)];
}

int find_in_denom_table(std::string_view s) {
	int ret = 0;
	for (const std::string_view& c : currency_denom_table()) {
		if (s == c)
			return ret;
		++ret;
	}
	throw std::runtime_error{"unknown character denominator"};
}

bool in_range(Currency c) {
	return Currency::USD <= c && c <= Currency::CHF;
}

double conversion_rate(Currency from, Currency to) {
	static constexpr std::array<std::array<double, 5>, 5> rate_tbl = {{
		{1, 0.96, 391.48, 7.16, 0.91},		// from USD
		{1.04, 1, 408.20, 7.46, 0.94},		// from EUR
		{0.0026, 0.0024, 1, 0.018, 0.0023},	// from HUF
		{0.14, 0.13, 54.70, 1, 0.13},		// from DKK
		{1.1, 1.06, 432.32, 7.90, 1}		// from CHF
	}};
	if (!(in_range(from) && in_range(to)))
		throw std::runtime_error{"Currency out of range"};
	return rate_tbl[to_int(from)][to_int(to)];
}

Money& Money::operator+=(const Money& rhs) {
	a += rhs.a * conversion_rate(rhs.c, c);
	return *this;
}

Money& Money::operator-=(const Money& rhs) {
	a -= rhs.a * conversion_rate(rhs.c, c);
	return *this;
}

long int Money::round(double d) const {
	long int value = d * 100;
	// To check digit of tenth of a cent
	long int helper = d * 1000;
	if (helper % 10 > 4)
		++value;
	return value;
}

Money operator+(const Money& lhs, const Money& rhs) {
	Money ret = lhs;
	ret += rhs;
	return ret;
}

Money operator-(const Money& lhs, const Money& rhs) {
	Money ret = lhs;
	ret -= rhs;
	return ret;
}

std::istream& operator>>(std::istream& is, Money& rhs) {
	// c1-c3 hold the currency denominations
	char c1{};
	char c2{};
	char c3{};
	double val = 0.0;
	if (is >> c1 >> c2 >> c3 >> val) {
		std::string m_denom{c1, c2, c3};
		Currency cur{find_in_denom_table(m_denom)};
		rhs.set_currency(cur);
		rhs = val;
	}
	return is;
}

std::ostream& operator<<(std::ostream& os, const Money& rhs) {
	long int value = rhs.amount();
	Currency cur = rhs.currency();
	return os << to_denom(cur) << value / 100 << '.' << std::abs(value % 100);
}
