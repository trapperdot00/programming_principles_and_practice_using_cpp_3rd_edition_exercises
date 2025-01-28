#include "Rational.h"

#include <iostream>

int main() {
	Rational r1, r2;
	while (std::cin >> r1 >> r2) {
		std::cout << r1 << " + " << r2 << " = " << r1 + r2 << " = " << double(r1 + r2) << "\n";
		std::cout << r1 << " - " << r2 << " = " << r1 - r2 << " = " << double(r1 - r2) << "\n";
		std::cout << r1 << " * " << r2 << " = " << r1 * r2 << " = " << double(r1 * r2) << "\n";
		std::cout << r1 << " / " << r2 << " = " << r1 / r2 << " = " << double(r1 / r2) << "\n\n";

	}
}
