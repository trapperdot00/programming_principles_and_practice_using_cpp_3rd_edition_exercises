#include <iostream>

int main()
{
	std::cout << "Enter three integers: ";
	int val1 = 0;
	int val2 = 0;
	int val3 = 0;
	std::cin >> val1 >> val2 >> val3;
	if (val1 < val2) {
		if (val1 < val3) {
			std::cout << val1 << ", ";
			if (val2 > val3) {
				std::cout << val3 << ", " << val2 << '\n';
			} else {
				std::cout << val2 << ", " << val3 << '\n';
			}
		} else if (val1 > val3) {
			// val3 < val1 < val2
			std::cout << val3 << ", " << val1 << ", " << val2 << '\n';
		} else {
			std::cout << val1 << ", " << val3 << ", " << val2 << '\n';
		}
	} else if (val1 > val2) {
		if (val1 > val3) {
			if (val2 > val3) {
				std::cout << val3 << ", " << val2 << ", ";
			} else {
				std::cout << val2 << ", " << val3 << ", ";
			}
			std::cout << val1 << '\n';
		} else {
			// val1 == val3 && val1 > val2
			std::cout << val2 << ", " << val1 << ", " << val3 << '\n';
		}
	} else {
		// val1 == val2
		if (val1 > val3) {
			std::cout << val3 << ", " << val1 << ", " << val2 << '\n';
		} else {
			std::cout << val1 << ", " << val2 << ", " << val3 << '\n';
		}
	}
}
