#include <string>
#include <iostream>
#include <cctype>
#include <vector>

bool only_numeric(const std::string& s) {
	if (s.empty())
		return false;
	for (std::string::const_iterator it = s.cbegin(); it != s.cend(); ++it)
		if (!std::isdigit(*it))
			return false;
	return true;
}

int main()
{
	std::cout << "Enter up to 4 digits: ";
	std::string digits;
	if (!(std::cin >> digits) || digits.size() > 4)
		throw std::runtime_error("Max 4 digits!");
	if (!only_numeric(digits))
		throw std::runtime_error("Only digits!");

	const std::vector<std::string> amounts = {
		"thousand", "hundred", "ten", "one"
	};
	std::cout << digits << " is";
	for (size_t i = 0; i < digits.size(); ++i) {
		int digit = digits[i] - '0';
//		size_t j = 1 + i;
		size_t j = amounts.size() - digits.size() + i;
		if (i != 0)
			std::cout << " and";
		std::cout << ' ' << digit << ' '
			<< (digit == 1 ? amounts[j] : amounts[j] + 's');
	}
	std::cout << ".\n";
}
