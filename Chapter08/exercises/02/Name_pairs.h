#ifndef NAME_PAIRS_H
#define NAME_PAIRS_H

#include <string>
#include <string_view>
#include <vector>
#include <iostream>
#include <algorithm>
#include <utility>
#include <stdexcept>

// Class that holds name-age pairs
class Name_pairs {
public:
	void read_names();
	void read_ages();
	void print() const;
	void sort();
private:

	std::vector<std::string> name;
	std::vector<double> age;
};

template <typename T>
auto only_unique_elements(std::vector<T>) -> bool;

#endif
