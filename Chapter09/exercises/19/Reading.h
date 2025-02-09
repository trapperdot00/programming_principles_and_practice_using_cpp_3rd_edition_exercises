#ifndef READING_H
#define READING_H

#include <iostream>
#include <stdexcept>

struct Reading {
	int hour;
	double temperature;
	char scale;
};

std::ostream& operator<<(std::ostream&, const Reading&);
std::istream& operator>>(std::istream&, Reading&);

// To enable sorting with STL algorithms with this comparator function
bool compare_temp(const Reading&, const Reading&);

double f_to_c(double);
double c_to_f(double);

#endif
