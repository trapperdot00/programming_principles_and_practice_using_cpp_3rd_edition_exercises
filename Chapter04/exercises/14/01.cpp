#include <vector>
#include <string>
#include <iostream>
#include <cstddef>
#include <cctype>
#include <iomanip>

class sum_error{};
class not_found{};

std::string make_lowercase(std::string s) {
	for (char &c : s)
		c = tolower(c);
	return s;
}

const std::vector<std::string>& get_day_names() {
	static const std::vector<std::string> vec = {
		"monday", "tuesday", "wednesday", "thursday",
		"friday", "saturday", "sunday"
	};
	return vec;
}

int sum(const std::vector<int>& vec) {
	if (vec.empty())
		throw sum_error{};
	int sum = 0;
	for (size_t i = 0; i < vec.size(); ++i) {
		sum += vec[i];
	}
	return sum;
}

void print_all(const std::vector<std::vector<int>>& vec, std::size_t rej) {
	for (size_t i = 0; i < 7; ++i) try {
		int curr_sum = sum(vec[i]);
		std::cout << std::setw(20) << std::left
			<< get_day_names()[i] + ":" << curr_sum << '\n'
			<< std::setw(0) << std::right;
	} catch (sum_error& e) {
		// No work to do here
		// Don't print days with no value
	}
	if (rej)
		std::cout << std::setw(20) << std::left
			<< "Rejected values:" << rej << '\n'
			<< std::setw(0) << std::right;
}

size_t convert_to_day_index(const std::string &s) {
	constexpr size_t threshold = 3;
	std::string day = make_lowercase(s);
	for (size_t i = 0; i < 7; ++i) {
		const std::string &curr_day = get_day_names()[i];
		if (day == curr_day)
			return i;

		// Accept abbreviations, such as "mon" or "tue"
		// with a specified lower threshold of size
		if (day.size() >= threshold && curr_day.find(day) == 0)
			return i;
	}

	throw not_found{};
}

int main()
{
	std::vector<std::vector<int>> days_values(7);
	std::cout << "Enter day-of-the-week, value pairs: ";
	std::string day;
	int value = 0;
	size_t rejected_count = 0;
	while (std::cin >> day >> value) try {
		days_values[convert_to_day_index(day)].push_back(value);
	} catch (not_found& e) {
		std::cerr << "Invalid day!\n";
		++rejected_count;
	}
	print_all(days_values, rejected_count);
}
