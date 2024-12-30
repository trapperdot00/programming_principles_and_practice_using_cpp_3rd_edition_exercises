#include <iostream>
#include <string>
#include <vector>

const std::vector<std::string> numbers = {
	"zero", "one", "two", "three", "four",
	"five", "six", "seven", "eight", "nine"
};

bool single_digit(const std::string& s) {
	return s.size() == 1 && s[0] <= '9' && s[0] >= '0';
}

std::size_t convert(const std::string &num) {
	if (single_digit(num)) {
		return num[0] - '0';
	} else {
		std::size_t i = 0;
		while (i < numbers.size() && numbers[i] != num)
			++i;
		return i;
	}
}

int main()
{
	std::string val1, val2;
	char op = ' ';
	while (std::cin >> val1 >> val2 >> op) {
		int num1 = convert(val1);
		int num2 = convert(val2);
		if (num1 < numbers.size() && num2 < numbers.size()) {
			switch (op) {
			case '+':
				std::cout << "The sum of " << num1 << " and " << num2
					<< " is " << num1 + num2 << '\n';
				break;
			case '-':
				std::cout << "The difference of " << num1 << " and " << num2
					<< " is " << num1 - num2 << '\n';
				break;
			case '*':
				std::cout << "The product of " << num1 << " and " << num2
					<< " is " << num1 * num2 << '\n';
				break;
			case '/':
				std::cout << "The quotient of " << num1 << " and " << num2
					<< " is " << num1 / num2 << '\n';
				break;
			default:
				std::cout << "Invalid operator!\n";
			}
		} else
			std::cout << "Invalid number!\n";
	}
}
