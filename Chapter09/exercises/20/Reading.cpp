#include "Reading.h"

bool is_valid(const Reading& r) {
	if (r.day < 1 || r.day > 31)
		return false;
	if (r.hour < 0 || r.hour > 23)
		return false;
	if (r.temp < implausible_min || r.temp > implausible_max)
		return false;
	return true;
}

std::istream& operator>>(std::istream& is, Reading& rhs) {
	char c1 = 0;
	if (is >> c1 && c1 != '(') {
		is.unget();
		is.clear(std::ios::failbit);
		return is;
	}
	char c2 = 0;
	if ((is >> rhs.day >> rhs.hour >> rhs.temp >> c2) && c2 != ')')
		throw std::runtime_error{"bad reading"};
	return is;
}
