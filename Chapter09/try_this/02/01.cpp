#include <format>
#include <iostream>

int main() {
	constexpr double d = 1234.56789;
	// This prints the string specified, with curly braces replaced by variables
	// with a set of formatting directives:
	//  - {:12}		width of 12
	//  - {:12.8f}	width of 12, precision of 8, fixed mode:
	//  				the precision (8) is the number of digits after the decimal point
	//  - {:30.20e}	width of 30, precision of 20, scientific mode:
	//  				the precision (20) is the number of digits after the decimal point
	// d is inserted into each slot indicated by {}
	std::cout << std::format("- {:12} - {:12.8f} - {:30.20e} -\n", d, d, d);
	
	// - {:#^12}	width of 12, aligned to the center, filled with '#'
	// - {:+}		prints the sign even if the number is positive
	// - {:X>30a}	width of 30, aligned right, filled with 'X', hexfloat
	std::cout << std::format("- {:#^12} - {:+} - {:X>30a}\n", d, d, d);
}
