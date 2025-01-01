#include <iostream>
#include <stdexcept>

double ctok(double c) {
	double k = c + 273.15;	// int to double to avoid narrowing
	return k;	// return the calculated value and added a semicolon
}

int main()
try {
	double c = 0;
	std::cin >> c;		// read into c instead of the non-existent 'd'
	if (c < -273.15)
		throw std::runtime_error("Temperature less than absolute zero!");
	double k = ctok(c);	// pass c instead of "c"
	std::cout << k << '\n';	// std::cout instead of "Cout"
} catch (std::exception &e) {
	std::cerr << "error: " << e.what() << '\n';
}
