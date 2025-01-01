#include <iostream>
#include <stdexcept>
#include <string>

template <typename T>
void expect(T func, const std::string &msg) {
	if (!func())
		throw std::runtime_error(msg);
}

double ctok(double c) {
	expect([&]{ return c >= -273.15; }, "ctok argument less than absolute zero!");
	double k = c + 273.15;
	return k;
}

double ktoc(double k) {
	expect([&]{ return k >= 0; }, "ktoc argument less than absolute zero!");
	double c = k - 273.15;
	return c;
}

double ctof(double c) {
	expect([&]{ return c >= -273.15; }, "ctof argument less than absolute zero!");
	double f = c * 9/5 + 32;
	return f;
}

double ftoc(double f) {
	expect([&]{ return f >= -459.67; }, "ftoc argument less than absolute zero!");
	double c = (f - 32) * 5/9;
	expect([&]{ return c >= -273.15; }, "ftoc result less than absolute zero!");
	return c;
}

double ktof(double k) {
	return ctof(k - 273.15);
}

double ftok(double f) {
	return ftoc(f) + 273.15;
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
					expect([&]{ return value >= -273.15; }, "Less than absolute zero!");
					std::cout << value << "C\n";
					break;
				case 'F':
					std::cout << ctof(value) << "F\n";
					break;
				default:
					throw std::runtime_error("Invalid unit to convert to!");
					break;
			}
			break;
		case 'K':
			switch (to_unit) {
				case 'C':
					std::cout << ktoc(value) << "C\n";
					break;
				case 'F':
					std::cout << ktof(value) << "F\n";
					break;
				case 'K':
					expect([&]{ return value >= 0; }, "Less than absolute zero!");
					std::cout << value << "K\n";
					break;
				default:
					throw std::runtime_error("Invalid unit to convert to!");
					break;
			}
			break;
		case 'F':
			switch (to_unit) {
				case 'C':
					std::cout << ftoc(value) << "C\n";
					break;
				case 'F':
					expect([&]{ return value >= -459.67; }, "Less than absolute zero!");
					std::cout << value << "F\n";
					break;
				case 'K':
					std::cout << ftok(value) << "K\n";
					break;
				default:
					throw std::runtime_error("Invalid unit to convert to!");
					break;
			}
			break;
		default:
			throw std::runtime_error("Invalid unit to convert from!");
			break;
	}
} catch (std::exception& e) {
	std::cerr << "error: " << e.what() << '\n';
}

