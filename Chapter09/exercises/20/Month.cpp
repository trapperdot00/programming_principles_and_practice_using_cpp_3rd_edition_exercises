#include "Month.h"

const std::vector<std::string> month_input_tbl = {
	"-not a month-",
	"jan", "feb", "mar", "apr", "may", "jun",
	"jul", "aug", "sep", "oct", "nov", "dec"
};

const std::vector<std::string> month_output_tbl = {
	"-not a month-",
	"January", "February", "March", "April", "May", "June",
	"July", "August", "September", "October", "November", "December"
};

int month_to_int(const std::string& s) {
	for (int i = 1; i < 13; ++i)
		if (month_input_tbl[i] == s)
			return i;
	return 0;
}

std::string int_to_month(int i) {
	if (i < 1 || i > 12)
		throw std::runtime_error{"bad month index"};
	return month_output_tbl[i];
}

void end_of_loop(std::istream& is, char term, const std::string& msg) {
	if (is.fail()) {
		is.clear();
		char ch = 0;
		if (is >> ch && ch == term)
			return;
		throw std::runtime_error{msg};
	}
}

std::istream& operator>>(std::istream& is, Month& m) {
	char c1 = 0;
	if (is >> c1 && c1 != '{') {
		is.unget();
		is.clear(std::ios::failbit);
		return is;
	}

	std::string month_marker;
	std::string mm;
	is >> month_marker >> mm;
	if (!is || month_marker != "month")
		throw std::runtime_error{"bad start of month"};
	m.month = month_to_int(mm);

	int duplicates = 0;
	int invalids = 0;
	for (Reading r; is >> r; ) {
		if (is_valid(r)) {
			if (m.days[r.day].temp[r.hour] != not_a_reading)
				++duplicates;
			m.days[r.day].temp[r.hour] = r.temp;
		} else
			++invalids;
	}
	if (invalids)
		throw std::runtime_error{"invalid readings in month " + std::to_string(invalids)};
	if (duplicates)
		throw std::runtime_error{"duplicate readings in month " + std::to_string(duplicates)};

	end_of_loop(is, '}', "bad end of month");
	return is;
}
