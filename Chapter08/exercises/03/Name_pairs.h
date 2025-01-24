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
// Holds the same amount of names and ages
// Names are unique
class Name_pairs {
public:
	Name_pairs(const std::vector<std::string>& n, const std::vector<double>& a)
		: name(n), age(a) {}
	Name_pairs(std::vector<std::string>&& n, std::vector<double>&& a)
		: name(std::move(n)), age(std::move(a)) {}
	void read_names();
	void read_ages();
	void sort();

	std::vector<std::string> names() const { return name; }
	std::vector<double> ages() const { return age; }
private:

	std::vector<std::string> name;
	std::vector<double> age;
};

template <typename T>
auto only_unique_elements(std::vector<T>) -> bool;

std::ostream& operator<<(std::ostream&, const Name_pairs&);
bool operator==(const Name_pairs&, const Name_pairs&);
bool operator!=(const Name_pairs&, const Name_pairs&);

#endif
