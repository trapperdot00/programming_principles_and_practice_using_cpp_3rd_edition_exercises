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

Month operator++(Month& m, int) {
	Month old = m;
	++m;
	return old;
}

Month& operator+=(Month& m, int n) {
	int value = (to_int(m) - 1 + n) % 12;
	if (value < 0)
		value += 12;
	m = Month{value + 1};
	return m;
}

Month& operator--(Month& m) {
	m = (m == Month::jan) ? Month::dec : Month{to_int(m)-1};
	return m;
}

Month operator--(Month& m, int) {
	Month old = m;
	--m;
	return old;
}

Month& operator-=(Month& m, int n) {
	int value = (to_int(m) - 1 - n) % 12;
	if (value < 0)
		value += 12;
	m = Month{value + 1};
	return m;
}

bool operator==(const Year& lhs, const Year& rhs) {
	return lhs.y == rhs.y;
}

int to_int(Day d) {
	return static_cast<int>(d);
}

Day int_to_day(int x) {
	if (x < to_int(Day::Monday) || to_int(Day::Sunday) < x)
		throw std::runtime_error{"bad day"};
	return Day{x};
}

std::string_view translate(Day d) {
	static constexpr std::array<std::string_view, 7> day_tbl = {
		"Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"
	};
	return day_tbl[to_int(d)];
}

Day& operator++(Day& d) {
	d = (d == Day::Sunday) ? Day::Monday : Day{to_int(d)+1};
	return d;
}

Day operator++(Day& d, int) {
	Day old = d;
	++d;
	return old;
}

Day& operator+=(Day& d, int n) {
	int index = (to_int(d) + n) % 7;
	if (index < 0)
		index += 7;
	d = Day{index};
	return d;
}

Day& operator--(Day& d) {
	d = (d == Day::Monday) ? Day::Sunday : Day{to_int(d)-1};
	return d;
}

Day operator--(Day& d, int) {
	Day old = d;
	--d;
	return old;
}

Day& operator-=(Day& d, int n) {
	int index = (to_int(d) - n) % 7;
	if (index < 0)
		index += 7;
	d = Day{index};
	return d;
}

Day operator+(const Day& d, int n) {
	Day ret = d;
	ret += n;
	return ret;
}

Day operator-(const Day& d, int n) {
	Day ret = d;
	ret -= n;
	return ret;
}

void Date::add_month(int n) {
	int month_num = to_int(m) + n - 1;
	int remainder_months = month_num % 12;
	int passed_years = month_num / 12;
	if (remainder_months < 0)
		--passed_years;
	y.y += passed_years;
	m += n;
	int daynum = number_of_days(m);
	// If day exceeds the maximum day of a month,
	// adjust to last day
	if (d > daynum)
		d = daynum;
}

void Date::add_day(int n) {
	int days = d + n;
	int days_in_curr_month = number_of_days(m);

	// Walk month-by-month and adjust days
	// until it becomes valid to assign it to d
	// within the current month
	while (days_in_curr_month < days) {
		if (m == Month::dec)
			++y.y;
		++m;
		days -= days_in_curr_month;
		days_in_curr_month = number_of_days(m, leapyear(y.y));
	}
	while (days <= 0) {
		if (m == Month::jan)
			--y.y;
		--m;
		days += days_in_curr_month;
		days_in_curr_month = number_of_days(m, leapyear(y.y));
	}
	d = days;
}

Day Date::day_of_the_week() const {
	Day day = starting_day_of_the_week(y.y);
	Date date{y, Month::jan, 1};
	while (date != *this) {
		date.add_day(1);
		++day;
	}
	return day;
}

bool Date::is_valid() const {
	// Check month validity
	if (to_int(m) < 1 || 12 < to_int(m))
		return false;
	// Check day validity
	if (d < 1 || number_of_days(m, leapyear(y.y)) < d)
		return false;
	return true;
}

bool leapyear(int y) {
	return y % 4 == 0 && ((y % 100 != 0) || (y % 400 == 0));
}

Day starting_day_of_the_week(int year) {
	// Start counting from 2001,
	// where the starting day-of-the-week
	// is a Monday
	int curr_year = 2001;
	Day ret{Day::Monday};
	// Changes forwards (exact opposite for backwards):
	//  - leapyear to a non-leapyear:		+2
	//  - non-leapyear to a non-leapyear:	+1
	//  - non-leapyear to a leapyear:		+1

	if (curr_year == year)
		return ret;

	// Move towards the given year by steps of one,
	// changing the day of the week based on jumps
	// indicated by leapyears
	while (curr_year < year) {
		if (leapyear(curr_year) && !leapyear(curr_year+1))
			ret += 2;
		else if (!leapyear(curr_year) && !leapyear(curr_year+1))
			++ret;
		else if (!leapyear(curr_year) && leapyear(curr_year+1))
			++ret;
		else
			throw std::runtime_error{"leapyear to leapyear jump in day_of_the_week"};
		++curr_year;
	}
	while (year < curr_year) {
		if (!leapyear(curr_year) && leapyear(curr_year-1))
			ret -= 2;
		else if (!leapyear(curr_year) && !leapyear(curr_year-1))
			--ret;
		else if (leapyear(curr_year) && !leapyear(curr_year-1))
			--ret;
		else
			throw std::runtime_error{"leapyear to leapyear jump in day_of_the_week"};
		--curr_year;
	}
	return ret;
}

int number_of_days(int y) {
	return leapyear(y) ? 366 : 365;
}

int number_of_days(Month month, bool is_leapyear) {
	switch (month) {
	case Month::jan:
		return 31;
	case Month::feb:
		return is_leapyear ? 29 : 28;
	case Month::mar:
		return 31;
	case Month::apr:
		return 30;
	case Month::may:
		return 31;
	case Month::jun:
		return 30;
	case Month::jul:
		return 31;
	case Month::aug:
		return 31;
	case Month::sep:
		return 30;
	case Month::oct:
		return 31;
	case Month::nov:
		return 30;
	case Month::dec:
		return 31;
	default:
		throw std::runtime_error{"invalid month for number_of_days"};
	}
}

Date next_workday(const Date& d) {
	Date ret = d;
	switch (ret.day_of_the_week()) {
	case Day::Friday:
		ret.add_day(3);
		break;
	case Day::Saturday:
		ret.add_day(2);
		break;
	default:
		ret.add_day(1);
		break;
	}
	return ret;
}

int week_of_year(const Date& d) {
	// Init to first week
	Date date{d.year(), Month::jan, 1};
	int week_count = 1;
	while (date != d) {
		// Calculate with Sunday as the first day of the week
		if (date.day_of_the_week() == Day::Saturday)
			++week_count;
		date.add_day(1);
	}
	return week_count;
}

bool operator==(const Date& lhs, const Date& rhs) {
	return lhs.year() == rhs.year()
		&& lhs.month() == rhs.month()
		&& lhs.day() == rhs.day();
}

bool operator!=(const Date& lhs, const Date& rhs) {
	return !(lhs == rhs);
}

std::ostream& operator<<(std::ostream& os, Month m) {
	return os << month_tbl[to_int(m)];
}

std::ostream& operator<<(std::ostream& os, Date d) {
	return os << d.year().y << '/' << d.month() << '/' << d.day();
}

std::ostream& operator<<(std::ostream& os, Day d) {
	return os << translate(d);
}
