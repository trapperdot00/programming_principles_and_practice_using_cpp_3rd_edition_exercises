#include <iostream>

int main() {
	constexpr double d = 1234567.89;

	// Fixed is the most accurate, since its precision (6)
	// is the number of digits after the decimal point,
	// scientific only displays one digit before the decimal point
	// so it displays less digits overall than fixed,
	// defaultfloat's digitcount is all of the digits
	std::cout << std::defaultfloat << d << '\t'
		<< std::fixed << d << '\t'
		<< std::scientific << d << '\n';
}
