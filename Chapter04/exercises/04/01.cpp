#include <iostream>
#include <stdexcept>

double ctok(double c) {
	if (c < -273.15)
		throw std::runtime_error("Temperature less than absolute zero!");

	double k = c + 273.15;	// int to double to avoid narrowing
	return k;	// return the calculated value and added a semicolon
}	// can't handle here, as we want to use the returned value in main()

int main()
try {
	double c = 0;
	std::cin >> c;		// read into c instead of the non-existent 'd'
	double k = ctok(c);	// pass c instead of "c"
	std::cout << k << '\n';	// std::cout instead of "Cout"
} catch (std::exception& e) {
	std::cerr << "error: " << e.what() << '\n';
}

