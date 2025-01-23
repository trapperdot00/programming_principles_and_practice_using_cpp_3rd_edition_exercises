#include <vector>
#include <stdexcept>
#include <iostream>
#include <utility>

int maxv(const std::vector<int>& vec) {
	if (vec.empty())
		throw std::runtime_error{"vector has no elements"};
	int max = vec[0];
	for (size_t i = 1; i < vec.size(); ++i) {
		if (max < vec[i])
			max = vec[i];
	}
	return max;
}

int main() {
	std::vector<int> numbers;
	std::cout << "Enter numbers: ";
	for (int temp; std::cin >> temp; )
		numbers.push_back(std::move(temp));

	std::cout << "The maximum value in the given elements: " << maxv(numbers) << '\n';
}
