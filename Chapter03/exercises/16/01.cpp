#include <string>
#include <iostream>
#include <vector>
#include <algorithm>

std::string min(const std::vector<std::string> &vec) {
	if (vec.empty())
		return "";
	int min_index = 0;
	for (int i = 1; i < vec.size(); ++i) {
		if (vec[i] < vec[min_index])
			min_index = i;
	}
	return vec[min_index];
}

std::string max(const std::vector<std::string> &vec) {
	if (vec.empty())
		return "";
	int max_index = 0;
	for (int i = 1; i < vec.size(); ++i) {
		if (vec[i] > vec[max_index])
			max_index = i;
	}
	return vec[max_index];
}

std::string mode(std::vector<std::string> vec) {
	if (vec.empty())
		return "";
	std::ranges::sort(vec);
	int mode_index = 0;
	int mode_count = 0;
	int curr_count = 0;
	for (int i = 1; i < vec.size(); ++i) {
		if (vec[i-1] == vec[i]) {
			++curr_count;
		} else {
			if (curr_count > mode_count) {
				mode_index = i - 1;
				mode_count = curr_count;
			}
			curr_count = 0;
		}
	}
	if (curr_count > mode_count) {
		mode_index = vec.size() - 1;
	}
	return vec[mode_index];
}

int main()
{
	std::vector<std::string> words;

	for (std::string temp; std::cin >> temp; )
		words.push_back(temp);

	std::cout << "Min:\t" << min(words)
		<< "\nMax:\t" << max(words)
		<< "\nMode:\t" << mode(words) << '\n';
}
