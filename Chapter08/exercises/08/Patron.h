#ifndef PATRON_H
#define PATRON_H

#include <string>
#include <iostream>

class Patron {
public:
	Patron(const std::string& name, size_t fee)
		: n(name), c(current_card_no++), f(fee) {}
	Patron(const std::string& name) : Patron(name, 0) {}
	Patron() : Patron("") {}

	auto name() const -> std::string { return n; }
	constexpr auto cardno() const -> size_t { return c; }
	constexpr auto fees() const -> size_t { return f; }

	auto set_name(const std::string& s) { n = s; }
	constexpr void set_fee(size_t n) { f = n; }
private:
	// Card number that is assigned to the next created Patron
	// Incremented by each construction of an object
	static size_t current_card_no;

	std::string n;	// Name of user
	size_t c;		// Library card number
	size_t f;	// Fees
};

constexpr auto owes(const Patron& p) -> bool {
	return p.fees() != 0;
}

std::ostream& operator<<(std::ostream&, const Patron&);

#endif
