#include <format>
#include <iostream>

int main() {
	int birth_year{2005};

	// Output birth year in decimal, hexadecimal, and octal form
	// positional indexing prevents passing the same argument three times:
	// "{0}" refers to the first argument after the format string,
	// "{0:x}" refers to the same argument, applies hexadecimal formatting,
	// "{0:o}" refers to the same, applies octal formatting
	// (could have used {0:d} instead of {0} but that's too verbose)
	std::cout << std::format("{0} {0:x} {0:o}\n", birth_year);
}
