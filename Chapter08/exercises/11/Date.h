#ifndef DATE_H
#define DATE_H

#include <iostream>
#include <stdexcept>
#include <vector>
#include <string>
#include <string_view>
#include <array>

enum class Month {
	jan=1, feb, mar, apr, may, jun, jul, aug, sep, oct, nov, dec
};

extern const std::vector<std::string> month_tbl;
int to_int(Month m);
Month int_to_month(int);
Month& operator++(Month&);
Month operator++(Month&, int);
Month& operator+=(Month&, int);

Month& operator--(Month&);
Month operator--(Month&, int);
Month& operator-=(Month&, int);

struct Year {
	int y;
};

bool operator==(const Year&, const Year&);

enum class Day {
	Monday, Tuesday, Wednesday, Thursday, Friday, Saturday, Sunday
};

int to_int(Day);
Day int_to_day(int);
std::string_view translate(Day);

Day& operator++(Day&);
Day operator++(Day&, int);
Day& operator+=(Day&, int);

Day& operator--(Day&);
Day operator--(Day&, int);
Day& operator-=(Day&, int);

Day operator+(const Day&, int);
Day operator-(const Day&, int);

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
	// Add months to a date, adjust years if necessary
	// If the new month has less days that d holds,
	// d is adjusted to hold the new month's number of days
	void add_month(int);
	// Add days but add months and years if necessary
	void add_day(int);

	Year year() const { return y; }
	Month month() const { return m; }
	int day() const { return d; }

	// Calculate the day of the week for the current date
	Day day_of_the_week() const;

private:
	bool is_valid() const;

	Year y{2001};
	Month m = Month::jan;
	int d = 1;
};

bool leapyear(int);

// Get day-of-the-week for the first day of a year
Day starting_day_of_the_week(int);

// Number of days in year
int number_of_days(int);
// Number of days in month
// Pass true if leapyear, false for not
int number_of_days(Month, bool = false);

Date next_workday(const Date&);
// Get number of week assuming first week
// falls on January 1st
// and first day of the week is Sunday (how weird!)
int week_of_year(const Date&);

bool operator==(const Date&, const Date&);
bool operator!=(const Date&, const Date&);
std::ostream& operator<<(std::ostream&, Date);
std::ostream& operator<<(std::ostream&, Month);
std::ostream& operator<<(std::ostream&, Day);

#endif
