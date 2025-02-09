#ifndef MONTH_H
#define MONTH_H

#include "Reading.h"
#include "Day.h"

#include <string>

constexpr int not_a_month = -1;

struct Month {
	int month = not_a_month;
	std::vector<Day> days = std::vector<Day>(32);
};

extern const std::vector<std::string> month_input_tbl;
extern const std::vector<std::string> month_output_tbl;
int month_to_int(const std::string&);
std::string int_to_month(int);
void end_of_loop(std::istream&, char, const std::string&);

std::istream& operator>>(std::istream&, Month&);

#endif
