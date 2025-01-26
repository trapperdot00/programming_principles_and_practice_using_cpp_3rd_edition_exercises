#include "Date.h"

const std::vector<std::string> month_tbl = {
	"Not a month", "January", "February", "March", "April", "May", "June",
	"July", "August", "September", "October", "November", "December"
};

int to_int(Month m) {
	return static_cast<int>(m);
}

Month int_to_month(int x) {
	if (x < to_int(Month::jan) || to_int(Month::dec) < x)
		throw std::runtime_error{"bad month"};
	return Month{x};
}

Month& operator++(Month& m) {
	m = (m == Month::dec) ? Month::jan : Month{to_int(m)+1};
	return m;
}

Month& operator+=(Month& m, int n) {
	int value = (to_int(m) - 1 + n) % 12;
	if (value < 0)
		value += 12;
	m = Month{value + 1};
	return m;
}

void Date::add_month(int n) {
	int months = to_int(m) - 1 + n;
	int years = months / 12;
	if (months < 0 && months % 12 != 0)
		--years;
	add_year(years);
	m += n;
}

void Date::add_day(int n) {
	int days = d - 1 + n;
	int months = days / 31;
	if (days < 0 && days % 31 != 0)
		--months;
	add_month(months);
	d = (days % 31 + 31) % 31 + 1;
}

bool Date::is_valid() const {
	// Check month validity
	if (to_int(m) < 1 || 12 < to_int(m))
		return false;
	// Check day validity
	if (d < 1 || 31 < d)
		return false;
	return true;
}

std::ostream& operator<<(std::ostream& os, Month m) {
	return os << month_tbl[to_int(m)];
}

std::ostream& operator<<(std::ostream& os, Date d) {
	return os << d.year().y << '/' << d.month() << '/' << d.day();
}
