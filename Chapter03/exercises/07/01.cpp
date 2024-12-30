#include <vector>
#include <iostream>
#include <string>
#include <cstddef>

const std::vector<std::string> numbers = {
	"zero", "one", "two", "three", "four",
	"five", "six", "seven", "eight", "nine"
};

std::string spell_out(std::size_t x) {
	if (x >= numbers.size())
		return "";
	return numbers[x];
}

int main()
{
	int val = 0;
	while (std::cin >> val) {
		std::cout << spell_out(val) << '\n';
	}
}
