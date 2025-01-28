#include "Date.h"

#include <iostream>
#include <iomanip>

int main() {
	Date d{Year(2001), Month::jan, 1};

	// Invalid week, week_of_year won't return this
	int prev_week = -1;
	int curr_week = 0;
	while (d.year().y != 2002) {
		curr_week = week_of_year(d);
		if (prev_week != curr_week) {
			if (prev_week != -1)
				std::cout << '\n';
			std::cout << "Week " << curr_week << ":\n";
		}
		std::cout << std::setw(12) << std::left << day_of_the_week(d.timestamp()) << d
			<< "\tNext workday: " << next_workday(d) << '\n';
		d.add_day(1);
		prev_week = curr_week;
	}
}
