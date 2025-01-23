#include <iostream>
#include <stdexcept>
#include <vector>

enum class Month {
	jan=1, feb, mar, apr, may, jun, jul, aug, sep, oct, nov, dec
};

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

std::ostream& operator<<(std::ostream& os, Month m) {
	return os << month_tbl[to_int(m)];
}

struct Year {
	int y;
};

class Date {
public:
	Date() {}
	Date(Year yy, Month mm, int dd)
		: y(yy), m(mm), d(dd) {
		if (!(is_valid()))
			throw std::runtime_error{"invalid date"};
	}
	Date(Year yy) : y(yy) {}

	void add_year(int n) {
		y.y += n;
	}
	// Add months but add years if necessary
	void add_month(int n) {
		int months = to_int(m) - 1 + n;
		int years = months / 12;
		if (months < 0 && months % 12 != 0)
			--years;
		add_year(years);
		m += n;
	}
	// Add days but add months and years if necessary
	void add_day(int n) {
		int days = d - 1 + n;
		int months = days / 31;
		if (days < 0 && days % 31 != 0)
			--months;
		add_month(months);
		d = (days % 31 + 31) % 31 + 1;
	}

	Year year() const { return y; }
	Month month() const { return m; }
	int day() const { return d; }

private:
	bool is_valid() const {
		// Check month validity
		if (to_int(m) < 1 || 12 < to_int(m))
			return false;
		// Check day validity
		if (d < 1 || 31 < d)
			return false;
		return true;
	}

	Year y{2001};
	Month m = Month::jan;
	int d = 1;
};

std::ostream& operator<<(std::ostream& os, Date d) {
	return os << d.year().y << '/' << d.month() << '/' << d.day();
}

int main() {
	Date today{Year{2020}, Month::feb, 2};

	Date tomorrow{today};
	tomorrow.add_day(1);

	std::cout << today << '\n' << tomorrow << '\n';

	// Date err1{Year{2000}, Month{13}, 1};		Error!
	// Date err2{Year{2000}, Month::dec, 37};	Error!
}
