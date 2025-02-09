#ifndef READING_H
#define READING_H

#include <iostream>

struct Reading {
	int hour;
	double temperature;
};

std::ostream& operator<<(std::ostream&, const Reading&);

#endif
