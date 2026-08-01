#include "Symbol_table.hpp"

#include <stdexcept>

double Symbol_table::get(const std::string& name) const {
	for (const Variable& v : var_table)
		if (v.name == name)
			return v.value;
	throw std::runtime_error("trying to read undefined variable " + name);
}

void Symbol_table::set(const std::string& name, double value) {
	for (Variable& v : var_table)
		if (v.name == name) {
			if (v.constant)
				throw std::runtime_error("trying to assign to constant");
			v.value = value;
			return;
		}
	throw std::runtime_error("trying to write undefined variable " + name);
}

bool Symbol_table::is_declared(const std::string& name) const {
	for (const Variable& v : var_table)
		if (v.name == name)
			return true;
	return false;
}

double Symbol_table::declare(const std::string& name, double value, bool constant) {
	if (is_declared(name))
		throw std::runtime_error(name + " declared twice");
	var_table.emplace_back(name, value, constant);
	return value;
}
