#ifndef VARIABLE_H
#define VARIABLE_H

#include <string>

struct Variable {
	Variable(std::string s, double d, bool c) : name(s), value(d), constant(c) {}
	std::string name;
	double value;
	bool constant;
};

#endif
