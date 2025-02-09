#ifndef YEAR_H
#define YEAR_H

#include "Month.h"
#include <iomanip>

struct Year {
	int year;
	std::vector<Month> months = std::vector<Month>(12);
};

// Prints readings in current year in ISO-8601 format YYYY-MM-DD
// Each reading goes in its own line
std::ostream& print_year(std::ostream&, const Year&);

// Read and print as structured file
std::istream& operator>>(std::istream&, Year&);
std::ostream& operator<<(std::ostream&, const Year&);

#endif
