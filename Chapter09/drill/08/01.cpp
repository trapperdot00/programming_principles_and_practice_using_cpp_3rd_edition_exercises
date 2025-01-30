#include <iostream>

int main() {
	int a{};
	int b{};
	int c{};
	int d{};

	// Numeric base manipulators are sticky, that is istreams and ostreams
	// remember their base after setting it and they need to be reset by us
	// manually

	// This code reads a as a decimal,
	// reads b as an octal,
	// reads c as a hexadecimal
	// and reads d as a hexadecimal, as we previously set std::hex and didn't change it

	// It could be easily confused for reading d as a decimal if we didn't know
	// that these manipulators are sticky

	// Best practice is to reset sticky manipulators after we are done with them to
	// their default states (std::hex to std::dec)
	std::cin >> a >> std::oct >> b >> std::hex >> c >> d;

	// We didn't manipulate std::cout yet, only std::cin,
	// it prints our numeric variables as decimal values
	std::cout << a << '\t' << b << '\t' << c << '\t' << d << '\n';
}
