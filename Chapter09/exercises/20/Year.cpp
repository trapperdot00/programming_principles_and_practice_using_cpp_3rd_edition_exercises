#include "Year.h"

std::ostream& print_year(std::ostream& os, const Year& y) {
	for (size_t i = 0; i < y.months.size(); ++i) {
		const Month& month = y.months[i];
		if (month.month == not_a_month)
			continue;
		for (size_t j = 0; j < month.days.size(); ++j) {
			const Day& day = month.days[j];
			for (double reading : day.temp) {
				if (reading == not_a_reading)
					continue;
				os << std::setw(4) << std::setfill('0') << y.year << '-'
					<< std::setw(2) << std::setfill('0') << month.month << '-'
					<< std::setw(2) << std::setfill('0') << j << ": "
					<< reading
					<< '\n';
			}
		}
	}
	return os;
}

std::istream& operator>>(std::istream& is, Year& y) {
	char ch = 0;
	is >> ch;
	if (ch != '{') {
		is.unget();
		is.clear(std::ios::failbit);
		return is;
	}

	std::string year_marker;
	int yy = 0;
	is >> year_marker >> yy;
	if (!is || year_marker != "year")
		throw std::runtime_error{"bad start of year"};
	y.year = yy;

	while (true) {
		Month m;
		if (!(is >> m))
			break;
		y.months[m.month] = m;
	}

	end_of_loop(is, '}', "bad end of year");
	return is;
}

std::ostream& operator<<(std::ostream& os, const Year& y) {
	os << "{ year " << y.year;
	for (size_t i = 0; i < y.months.size(); ++i) {
		// Months
		if (y.months[i].month != not_a_month) {
			os << " { month " << int_to_month(y.months[i].month);
			for (size_t j = 0; j < y.months[i].days.size(); ++j) {
				// Days
				for (size_t k = 0; k < y.months[i].days[j].temp.size(); ++k) {
					// Readings
					if (y.months[i].days[j].temp[k] != not_a_reading)
						os << " (" << j << ' ' << k << ' ' << y.months[i].days[j].temp[k] << ')';
				}
			}
			os << " }";
		}	
	}
	return os << " }";
}
