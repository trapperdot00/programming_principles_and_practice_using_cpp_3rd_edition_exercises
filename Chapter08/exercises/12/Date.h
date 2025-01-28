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
Month operator+(const Month&, int);

Month& operator--(Month&);
Month operator--(Month&, int);
Month& operator-=(Month&, int);
Month operator-(const Month&, int);

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
	Date(Year, Month, int);
	Date(Year yy);

	void add_year(int n);
	// Add months to a date, adjust years if necessary
	// If the new month has less days that d holds,
	// d is adjusted to hold the new month's number of days
	void add_month(int);
	// Add days but add months and years if necessary
	void add_day(int);

	Year year() const;
	Month month() const;
	int day() const;

	long int timestamp() const { return d; }

private:
	// Days since epoch (1970-01-01)
	long int d = 0;
};

long int to_timestamp(Year, Month, int);
long int days_until(Year);
long int days_until(Month, bool);

bool valid_timestamp(long int);
bool leapyear(int);

// Get day-of-the-week for a timestamp
Day day_of_the_week(long int);

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
std::ostream& operator<<(std::ostream&, Year);
std::ostream& operator<<(std::ostream&, Month);
std::ostream& operator<<(std::ostream&, Day);

#endif
