#include <iostream>
#include <stdexcept>
#include <limits>

class bad_char{};

int factorial(int num) {
	if (!num)
		return 1;
	if (num < 0)
		throw std::runtime_error("negative factorial!");
	for (int i = num-1; i > 1; --i) {
		if (std::numeric_limits<int>::max() / i < num)
			throw std::runtime_error("factorial overflow!");
		num *= i;
	}
	return num;
}

int permutation(int a, int b) {
	return factorial(a) / factorial(a-b);
}
int combination(int a, int b) {
	return permutation(a, b) / factorial(b);
}

int main()
try {
	bool b = true;
	while (b) try {
		std::cout << "Enter two numbers and 'P' or 'C' for permutation or combination or \"0 0 x\" to exit:\n";
		int num1 = 0;
		int num2 = 0;
		char ch = '\0';
		if (!(std::cin >> num1 >> num2 >> ch))
			throw std::runtime_error("No data!");
		switch (ch) {
		case 'P': case 'p':
			std::cout << "= " << permutation(num1, num2) << '\n';
			break;
		case 'C': case 'c':
			std::cout << "= " << combination(num1, num2) << '\n';
			break;
		case 'x': case 'X':
			if (!num1 && !num2) {
				b = false;
				break;
			}
			[[fallthrough]];
		default:
			throw bad_char{};
		}
	} catch (bad_char& e) {
		std::cerr << "Invalid character!\n";
	}
} catch (std::exception& e) {
	std::cerr << "error: " << e.what() << '\n';
}
