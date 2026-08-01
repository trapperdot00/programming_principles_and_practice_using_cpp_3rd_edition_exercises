#ifndef SYMBOL_TABLE_HPP
#define SYMBOL_TABLE_HPP

#include "Variable.hpp"
#include <string>
#include <vector>

class Symbol_table {
public:
	double get(const std::string&) const;
	void set(const std::string&, double);
	bool is_declared(const std::string&) const;
	double declare(const std::string&, double, bool);
private:
	std::vector<Variable> var_table;
};

#endif
