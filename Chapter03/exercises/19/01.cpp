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

// Returns the index of the found value or returns size()
int search(const std::vector<std::string> &vec, const std::string &s) {
	int i = 0;
	while (i < vec.size() && vec[i] != s)
	   	++i;
	return i;
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

	std::cout << "\nEnter name to find in the previously given values:\n";
	for (std::string s; std::cin >> s; ) {
		int pos = search(names, s);
		if (pos != names.size())
			std::cout << names[pos] << '\t' << scores[pos] << '\n';
		else
			std::cout << "name not found\n";
	}
}
