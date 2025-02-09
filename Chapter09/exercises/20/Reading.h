#ifndef READING_H
#define READING_H

#include <iostream>
#include <stdexcept>

constexpr int implausible_min = -200;
constexpr int implausible_max = 200;

struct Reading {
	int day;
	int hour;
	double temp;
};

bool is_valid(const Reading&);
std::istream& operator>>(std::istream&, Reading&);

#endif
