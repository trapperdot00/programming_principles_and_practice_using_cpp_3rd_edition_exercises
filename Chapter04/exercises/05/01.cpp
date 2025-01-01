#include <iostream>
#include <stdexcept>
#include <string>

template <typename T>
void expect(T func, const std::string &msg) {
	if (!func())
		throw std::runtime_error(msg);
}

double ctok(double c) {
	expect([&]{ return c >= -273.15; }, "Temperature less than absolute zero!");
	double k = c + 273.15;
	return k;
}

double ktoc(double k) {
	expect([&]{ return k >= 0; }, "Temperature less than absolute zero!");
	double c = k - 273.15;
	return c;
}

int main()
try {
	std::cout << "Enter temperature to convert (example: 10C K):\n";
	double value = 0.0;
	char from_unit = ' ';
	char to_unit = ' ';
	if (!(std::cin >> value >> from_unit >> to_unit))
		throw std::runtime_error("Invalid data!");
	
	switch (from_unit) {
		case 'C':
			switch (to_unit) {
				case 'K':
					std::cout << ctok(value) << "K\n";
					break;
				case 'C':
					std::cout << value << "C\n";
					break;
				default:
					throw std::runtime_error("Invalid unit to convert to!");
			}
			break;
		case 'K':
			switch (to_unit) {
				case 'C':
					std::cout << ktoc(value) << "C\n";
					break;
				case 'K':
					std::cout << value << "K\n";
					break;
				default:
					throw std::runtime_error("Invalid unit to convert to!");
			}
			break;
		default:
			throw std::runtime_error("Invalid unit to convert from!");
			break;
	}
} catch (std::exception& e) {
	std::cerr << "error: " << e.what() << '\n';
}

