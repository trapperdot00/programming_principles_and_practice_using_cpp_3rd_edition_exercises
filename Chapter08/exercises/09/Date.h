#ifndef DATE_H
#define DATE_H

#include <iostream>
#include <stdexcept>
#include <vector>

enum class Month {
	jan=1, feb, mar, apr, may, jun, jul, aug, sep, oct, nov, dec
};

extern const std::vector<std::string> month_tbl;
int to_int(Month m);
Month int_to_month(int);
Month& operator++(Month&);
Month& operator+=(Month&, int);

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

	void add_year(int n) { y.y += n; }
	// Add months but add years if necessary
	void add_month(int);
	// Add days but add months and years if necessary
	void add_day(int);

	Year year() const { return y; }
	Month month() const { return m; }
	int day() const { return d; }

private:
	bool is_valid() const;

	Year y{2001};
	Month m = Month::jan;
	int d = 1;
};

std::ostream& operator<<(std::ostream&, Date);
std::ostream& operator<<(std::ostream&, Month);

#endif
