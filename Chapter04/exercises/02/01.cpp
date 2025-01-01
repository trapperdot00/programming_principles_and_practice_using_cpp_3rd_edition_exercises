#include <iostream>

double ctok(double c) {
	double k = c + 273.15;	// int to double to avoid narrowing
	return k;	// return the calculated value and added a semicolon
}

int main()
{
	double c = 0;
	std::cin >> c;		// read into c instead of the non-existent 'd'
	double k = ctok(c);	// pass c instead of "c"
	std::cout << k << '\n';	// std::cout instead of "Cout"
}
