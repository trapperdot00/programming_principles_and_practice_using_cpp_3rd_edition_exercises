#ifndef READING_H
#define READING_H

#include <iostream>

struct Reading {
	int hour;
	double temperature;
};

std::ostream& operator<<(std::ostream&, const Reading&);
std::istream& operator>>(std::istream&, Reading&);

// To enable sorting with STL algorithms with this comparator function
bool compare_temp(const Reading&, const Reading&);

#endif
