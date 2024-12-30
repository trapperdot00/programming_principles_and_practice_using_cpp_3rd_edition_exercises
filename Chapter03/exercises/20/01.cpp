#include <vector>
#include <string>
#include <iostream>
#include <stdexcept>
#include <algorithm>

bool is_unique(std::vector<std::string> vec) {
	std::ranges::sort(vec);
	for (int i = 1; i < vec.size(); ++i) {
		if (vec[i - 1] == vec[i])
			return false;
	}
	return true;
}

// Returns indexes of found values
std::vector<int> search_all(const std::vector<int> &vec, int val) {
	std::vector<int> ret;
	for (int i = 0; i < vec.size(); ++i) {
		if (vec[i] == val)
			ret.push_back(i);
	}
	return ret;
}

int main()
{
	std::vector<std::string> names;
	std::vector<int> scores;

	std::cout << "Enter name-score pairs (NoName 0 to end reading):\n";
	std::string name;
	int score = 0;
	while (std::cin >> name >> score && (name != "NoName" || score != 0)) {
		names.push_back(name);
		scores.push_back(score);
	}
	if (!is_unique(names))
		throw std::runtime_error("repetition in names!");

	std::cout << "\nEnter value to find in the previously given values:\n";
	for (int val; std::cin >> val; ) {
		std::vector<int> found_indexes = search_all(scores, val);
		for (int pos : found_indexes) {
			std::cout << names[pos] << '\t' << scores[pos] << '\n';
		}
	}
}
