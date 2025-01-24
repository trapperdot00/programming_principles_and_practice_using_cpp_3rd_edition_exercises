#include "Name_pairs.h"

// Read names until quit
void Name_pairs::read_names() {
	// Used to end reading
	static constexpr std::string_view quit = "EXIT";
	std::cout << "Enter names ('" << quit << "' to end reading): ";
	for (std::string temp; std::cin >> temp && temp != quit; )
		name.push_back(std::move(temp));
	if (!only_unique_elements(name))
		throw std::runtime_error{"names cannot repeat"};
}

// Read ages for all names
void Name_pairs::read_ages() {
	if (name.empty())
		throw std::runtime_error{"no names"};
	std::cout << "Enter ages for names:\n";
	for (const std::string& n : name) {
		double a{};
		std::cout << n << ":\t";
		if (!(std::cin >> a))
			throw std::runtime_error{"age not provided for " + n};
		age.push_back(a);
	}
	if (name.size() != age.size())
		throw std::runtime_error{"number of names and ages don't match"};
}

// Sort elements based on the ordering of name
// Can only sort elements with unique names
void Name_pairs::sort() {
	// Hold sorted ages
	std::vector<double> new_age;
	// Hold original order of name
	auto name_copy{name};
	std::sort(name.begin(), name.end());
	for (size_t i = 0; i < name.size(); ++i) {
		for (size_t j = 0; j < name_copy.size(); ++j) {
			if (name[i] == name_copy[j])
				new_age.push_back(age[j]);
		}
	}
	age = std::move(new_age);
}

template <typename T>
auto only_unique_elements(std::vector<T> vec) -> bool {
	if (vec.size() <= 1)
		return true;
	std::sort(vec.begin(), vec.end());
	T last = vec.front();
	for (size_t i = 1; i < vec.size(); ++i) {
		if (last == vec[i])
			return false;
		last = vec[i];
	}
	return true;
}

std::ostream& operator<<(std::ostream& os, const Name_pairs& n) {
	auto names = n.names();
	auto ages = n.ages();
	for (size_t i = 0; i < names.size(); ++i) {
		os << names[i] << ":\t" << ages[i] << '\n';
	}
	return os;
}

bool operator==(const Name_pairs& lhs, const Name_pairs& rhs) {
	auto lhs_names = lhs.names();
	auto rhs_names = rhs.names();
	if (lhs_names.size() != rhs_names.size())
		return false;
	
	auto lhs_ages = lhs.ages();
	auto rhs_ages = rhs.ages();
	// Size is guaranteed to be the same now
	
	for (size_t i = 0; i != lhs_names.size(); ++i) {
		if (lhs_names[i] != rhs_names[i])
			return false;
		if (lhs_ages[i] != rhs_ages[i])
			return false;
	}
	return true;
}
bool operator!=(const Name_pairs& lhs, const Name_pairs& rhs) {
	return !(lhs == rhs);
}
