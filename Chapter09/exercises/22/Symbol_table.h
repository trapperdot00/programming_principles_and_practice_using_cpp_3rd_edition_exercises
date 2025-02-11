#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

#include "Variable.h"

#include <vector>
#include <stdexcept>

// Holds all variables in a vector
class Symbol_table {
public:
	double get(const std::string&) const;
	void set(const std::string&, double);
	bool is_declared(const std::string&) const;
	double declare(const std::string&, double, bool);
private:
	std::vector<Variable> var_table;
};

// Create a global object
extern Symbol_table symbols;

#endif
