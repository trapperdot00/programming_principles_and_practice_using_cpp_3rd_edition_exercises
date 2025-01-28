#ifndef RATIONAL_H
#define RATIONAL_H

#include <cmath>
#include <vector>
#include <iostream>

class Rational {
	friend std::istream& operator>>(std::istream&, Rational&);
public:
	Rational() {}
	Rational(int nn, int dd)
	: n{nn}, d{dd} {
		simplify();	
	}
	Rational(const Rational& rhs)
	: n(rhs.n), d(rhs.d) {}
	Rational& operator=(const Rational& rhs) {
		n = rhs.n;
		d = rhs.d;
		return *this;
	}

	int numerator() const { return n; }
	int denominator() const { return d; }

	Rational& operator+=(const Rational&);
	Rational& operator-=(const Rational&);
	Rational& operator*=(const Rational&);
	Rational& operator/=(const Rational&);

	// Calculate decimal form
	operator double() const { return double(n) / d; }
private:
	void simplify();

	int n = 0;
	int d = 0;
};

Rational operator+(const Rational&, const Rational&);
Rational operator-(const Rational&, const Rational&);
Rational operator*(const Rational&, const Rational&);
Rational operator/(const Rational&, const Rational&);

bool operator==(const Rational&, const Rational&);
bool operator!=(const Rational&, const Rational&);

std::ostream& operator<<(std::ostream&, const Rational&);
std::istream& operator>>(std::istream&, Rational&);

bool is_prime(int);

// Get first prime after given number
int next_prime(int);

// Get divisors of a number in a vector of ints,
// only positive divisors even for negative numbers
std::vector<int> divisors(int);
int greatest_common_divisor(int, int);
int least_common_multiple(int, int);

#endif
