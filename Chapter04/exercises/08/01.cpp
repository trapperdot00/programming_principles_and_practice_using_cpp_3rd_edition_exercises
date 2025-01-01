#include <stdexcept>
#include <iostream>
#include <vector>

int main()
try {
	std::cout << "Please enter the number of values you want to sum: ";
	int n = 0;
	if (!(std::cin >> n))
		throw std::runtime_error("No data!");
	if (n <= 0)
		throw std::runtime_error("Sum of no values!");

	std::cout << "Please enter some integers (press '|' to stop): ";
	std::vector<int> numbers;
	for (int temp; std::cin >> temp; )
		numbers.push_back(temp);

	if (numbers.empty())
		throw std::runtime_error("Empty series!");
	if (n > numbers.size())
		throw std::runtime_error("Sum of more elements than given size of series!");

	std::cout << "The sum of the first " << n << " numbers ( ";
	int sum = 0;
	for (int i = 0; i < n; ++i) {
		sum += numbers[i];
		std::cout << numbers[i] << ' ';
	}
	std::cout << ") is: " << sum << '\n';

	
} catch (std::exception& e) {
	std::cerr << "error: " << e.what() << '\n';
}
