#include "Rational.h"

Rational& Rational::operator+=(const Rational& rhs) {
	int new_denom = least_common_multiple(d, rhs.d);
	int lhs_delta = new_denom / d;
	int rhs_delta = new_denom / rhs.d;
	n = n * lhs_delta + rhs.n * rhs_delta;
	d = new_denom;
	simplify();
	return *this;
}

Rational& Rational::operator-=(const Rational& rhs) {
	int new_denom = least_common_multiple(d, rhs.d);
	int lhs_delta = new_denom / d;
	int rhs_delta = new_denom / rhs.d;
	n = n * lhs_delta - rhs.n * rhs_delta;
	d = new_denom;
	simplify();
	return *this;
}

Rational& Rational::operator*=(const Rational& rhs) {
	n *= rhs.n;
	d *= rhs.d;
	simplify();
	return *this;
}

Rational& Rational::operator/=(const Rational& rhs) {
	n *= rhs.d;
	d *= rhs.n;
	simplify();
	return *this;
}

void Rational::simplify() {
	int div = 1;
	do {
		div = greatest_common_divisor(n, d);
		n /= div;
		d /= div;
	} while (div != 1);
}

Rational operator+(const Rational& lhs, const Rational& rhs) {
	Rational ret = lhs;
	ret += rhs;
	return ret;
}

Rational operator-(const Rational& lhs, const Rational& rhs) {
	Rational ret = lhs;
	ret -= rhs;
	return ret;
}

Rational operator*(const Rational& lhs, const Rational& rhs) {
	Rational ret = lhs;
	ret *= rhs;
	return ret;
}

Rational operator/(const Rational& lhs, const Rational& rhs) {
	Rational ret = lhs;
	ret /= rhs;
	return ret;
}

bool operator==(const Rational& lhs, const Rational& rhs) {
	return lhs.numerator() == rhs.numerator()
		&& lhs.denominator() == rhs.denominator();
}

bool operator!=(const Rational& lhs, const Rational& rhs) {
	return !(lhs == rhs);
}

std::ostream& operator<<(std::ostream& os, const Rational& rhs) {
	return os << rhs.numerator() << '/' << rhs.denominator();
}

std::istream& operator>>(std::istream& is, Rational& rhs) {
	return is >> rhs.n >> rhs.d;
}

bool is_prime(int i) {
	if (i < 2)
		return false;
	for (int div = 2; div <= std::sqrt(i); ++div)
		if (i % div == 0)
			return false;
	return true;
}

int next_prime(int i) {
	do {
		++i;
	} while (!is_prime(i));
	return i;
}

std::vector<int> divisors(int i) {
	std::vector<int> ret;
	i = std::abs(i);
	while (i > 1) {
		int div = 2;
		while (i % div != 0) {
			div = next_prime(div);
		}
		i /= div;
		ret.push_back(div);
	}
	return ret;
}

int greatest_common_divisor(int i, int j) {
	i = std::abs(i);
	j = std::abs(j);
	if (j == 0)
		return i;
	return greatest_common_divisor(j, i % j);
}

int least_common_multiple(int i, int j) {
	return std::abs(i * j) / greatest_common_divisor(i, j);
}
