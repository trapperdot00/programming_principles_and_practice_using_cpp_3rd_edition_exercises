#include <vector>
#include <iostream>
#include <string>
#include <cstddef>

const std::vector<std::string> numbers = {
	"zero", "one", "two", "three", "four",
	"five", "six", "seven", "eight", "nine"
};

std::size_t digit(const std::string &num) {
	std::size_t x = 0;
	while (x < numbers.size() && numbers[x] != num)
		++x;
	return x;
}

int main()
{
	std::string val;
	while (std::cin >> val) {
		std::size_t num = digit(val);
		if (num < numbers.size())
			std::cout << num << '\n';
		else
			std::cout << "invalid digit" << std::endl;
	}
}
