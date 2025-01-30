#include <format>
#include <iostream>

int main() {
	int birth_year{2005};

	// Field width
	constexpr int width = 16;

	// Output birth year in decimal, hexadecimal, and octal form with labels
	// {1:{0}}		"Decimal" with width of variable width
	// {2:{0}}		"Hexadecimal" with width of var. width
	// {3:{0}}		"Octal" with width of var. width
	// {4:<{0}}		birth_year aligned left with width of var. width
	// {4:<{0}x}	birth_year in hexadecimal form aligned left with width of var. width
	// {4:<{0}o}	birth_year in octal form aligned left with width of var. width
	// 
	// it looks like strings are aligned implicitly left and non-strings right in the fields,
	// that's why I had to supply left-alignment for the integer
	std::cout << std::format("{1:{0}}{2:{0}}{3:{0}}\n{4:<{0}}{4:<{0}x}{4:<{0}o}\n",
		   	width, "Decimal", "Hexadecimal", "Octal", birth_year);
}
