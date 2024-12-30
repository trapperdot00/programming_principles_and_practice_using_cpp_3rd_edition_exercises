#include <iostream>
#include <vector>
#include <algorithm>

int get_mode(std::vector<int> vec) {
	std::ranges::sort(vec);
	int mode = vec[0];
	int count = 1;
	int curr_count = 1;
	int i = 1;
	while (i < vec.size()) {
		if (vec[i - 1] == vec[i]) {
			++curr_count;
		} else {
			if (curr_count > count) {
				mode = vec[i - 1];
				count = curr_count;
			}
			curr_count = 1;
		}
		++i;
	}

	if (curr_count > count) {
		mode = vec[i-1];
	}
	return mode;
}

int main()
{
	std::vector<int> numbers;

	for (int temp = 0; std::cin >> temp; )
		numbers.push_back(temp);

	if (!numbers.empty()) {
		int mode = get_mode(numbers);
		std::cout << "Mode:\t" << mode << '\n';
	} else {
		std::cout << "No data!\n";
	}
}
