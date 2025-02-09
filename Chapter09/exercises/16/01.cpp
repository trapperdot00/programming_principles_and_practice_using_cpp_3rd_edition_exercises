#include <fstream>
#include <iostream>
#include <string>
#include <stdexcept>
#include <vector>

auto sum(const std::vector<int>& vec) -> int {
	int sum = 0;
	for (int i : vec)
		sum += i;
	return sum;
}

auto read_file(const std::string& filename) -> std::vector<int> {
	std::ifstream ifs{filename};
	if (!ifs)
		throw std::runtime_error{"can't open " + filename + " for reading"};
	std::vector<int> numbers;
	for (int i = 0; ifs >> i; )
		numbers.push_back(i);
	return numbers;
}

int main() {
	std::cout << "Enter input filename: ";
	std::string filename;
	if (!(std::cin >> filename))
		throw std::runtime_error{"no data"};

	std::cout << "The sum of all numbers in "
		<< filename
		<< ": "
		<< sum(read_file(filename))
		<< '\n';
}
