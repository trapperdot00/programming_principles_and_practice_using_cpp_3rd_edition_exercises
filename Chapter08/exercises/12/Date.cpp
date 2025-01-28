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

Month operator+(const Month& m, int n) {
	Month ret = m;
	ret += n;
	return ret;
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

Month operator-(const Month& m, int n) {
	Month ret = m;
	ret -= n;
	return ret;
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

Date::Date(Year yy, Month mm, int dd)
	: d(to_timestamp(yy, mm, dd))
{}

Date::Date(Year yy)
	: d(to_timestamp(yy, Month::jan, 1))
{}

void Date::add_year(int n) {
	int i = 0;
	while (i != n) {
		Month prev_m = month();
		int daynum = number_of_days(year().y);
		if (i < n) {
			d += daynum;
			if (!valid_timestamp(d))
				throw std::runtime_error{"add_year goes out of range"};
			while (prev_m != month())
				--d;
			++i;
		} else {
			d -= daynum;
			if (!valid_timestamp(d))
				throw std::runtime_error{"add_year goes out of range"};
			while (prev_m != month())
				++d;
			--i;
		}
	}
}

void Date::add_month(int n) {
	int i = 0;
	while (i != n) {
		if (i < n) {
			int daynum = number_of_days(month(), leapyear(year().y));
			Month prev_m = month();
			d += daynum;
			// Handle day truncating:
			// for example: if going from January 31 to February,
			// since February has either only 28 or 29 days,
			// the next iteration will have 28 or 29 as day,
			// and when going to the succeeding months,
			// day will only be 28 or 29
			while (prev_m + 1 != month())
				--d;
			if (!valid_timestamp(d))
				throw std::runtime_error{"add_month goes out of range"};
			++i;
		} else {
			int prev_d = day();
			d -= prev_d;
			// Handle same truncating as above for positive n:
			// Dec 31 -> Nov 30 -> Oct 30 -> Sep 30
			while (prev_d < day())
				--d;
			if (!valid_timestamp(d))
				throw std::runtime_error{"add_month goes out of range"};
			--i;
		}
	}
}

void Date::add_day(int n) {
	if (d + n < 0)
		throw std::runtime_error{"date outside of representable range"};
	d += n;
}

Year Date::year() const {
	long int epoch = 0;
	Year ret{1970};
	while (epoch + number_of_days(ret.y) <= d) {
		epoch += number_of_days(ret.y);
		++ret.y;
	}
	return ret;
}

Month Date::month() const {
	long int epoch = to_timestamp(year(), Month::jan, 1);
	bool is_leapyear = leapyear(year().y);
	Month ret{Month::jan};
	while (epoch + number_of_days(ret, is_leapyear) <= d) {
		epoch += number_of_days(ret, is_leapyear);
		++ret;
	}
	return ret;
}

int Date::day() const {
	long int epoch = to_timestamp(year(), month(), 1);
	return d - epoch + 1;
}

long int to_timestamp(Year year, Month month, int day) {
	if (year.y < 1970)
		throw std::runtime_error{"year out of range in to_timestamp"};
	if (month < Month::jan || Month::dec < month)
		throw std::runtime_error{"month out of range in to_timestamp"};
	int month_days = number_of_days(month, leapyear(year.y));
	if (month_days < day || day < 1)
		throw std::runtime_error{"day out of range in to_timestamp"};
	return days_until(year) + days_until(month, leapyear(year.y)) + day - 1;
}

long int days_until(Year year) {
	if (year.y < 1970)
		throw std::runtime_error{"year out of range in days_until"};
	long int ret = 0;
	for (int curr_year = 1970; curr_year < year.y; ++curr_year)
		ret += number_of_days(curr_year);
	return ret;
}

long int days_until(Month month, bool is_leapyear) {
	if (month < Month::jan || Month::dec < month)
		throw std::runtime_error{"month out of range in days_until"};
	long int ret = 0;
	for (Month curr{Month::jan}; curr < month; ++curr)
		ret += number_of_days(curr, is_leapyear);
	return ret;
}

bool valid_timestamp(long int timestamp) {
	return 0 <= timestamp;
}

bool leapyear(int y) {
	return y % 4 == 0 && ((y % 100 != 0) || (y % 400 == 0));
}

Day day_of_the_week(long int timestamp) {
	if (timestamp < 0)
		throw std::runtime_error{"negative timestamp in starting_day_of_the_week"};
	int day_index = timestamp % 7;
	return Day{day_index} + 3;
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
	switch (day_of_the_week(ret.timestamp())) {
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
	long int epoch = to_timestamp(d.year(), Month::jan, 1);
	long int end_epoch = d.timestamp();
	int week_count = 1;
	while (epoch < end_epoch) {
		// Calculate with Sunday as the first day of the week
		if (day_of_the_week(epoch) == Day::Saturday)
			++week_count;
		++epoch;
	}
	return week_count;
}

bool operator==(const Date& lhs, const Date& rhs) {
	return lhs.timestamp() == rhs.timestamp();
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

std::ostream& operator<<(std::ostream& os, Year y) {
	return os << y.y;
}
