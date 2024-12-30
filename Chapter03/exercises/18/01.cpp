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

int main()
{
	std::vector<std::string> names;
	std::vector<int> scores;

	std::cout << "Enter name-score pairs (NoName 0 to stop reading):\n";
	std::string name;
	int score = 0;
	while (std::cin >> name >> score && (name != "NoName" || score != 0)) {
		names.push_back(name);
		scores.push_back(score);
	}
	if (!is_unique(names))
		throw std::runtime_error("repetition in names!");

	std::cout << "\nName-score pairs:\n";
	// It is guaranteed that both vectors have the same sizes!
	for (int i = 0; i < names.size(); ++i) {
		std::cout << names[i] << '\t' << scores[i] << '\n';
	}
}
