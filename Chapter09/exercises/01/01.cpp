#include <iostream>
#include <fstream>
#include <cctype>
#include <stdexcept>
#include <string>

// Get input from an istream character-by-character,
// and write the lowercase version of the read character
// into the given ostream
void print_lowercase(std::istream& is, std::ostream& os) {
	for (char c; is.get(c); )
		// Cast to char, cctype functions return int
		// (thank C for that)
		os << static_cast<char>(std::tolower(c));
}

int main() {
	std::cout << "Enter input filename: ";
	std::string infilename;

	std::cin >> infilename;
	std::ifstream ifs{infilename};
	if (!ifs)
		throw std::runtime_error{"can't open file: " + infilename};

	std::cout << "Enter output filename: ";
	std::string outfilename;

	// Input and output file cannot have the same name,
	// as that would result in data loss for the input file
	while (std::cin >> outfilename && outfilename == infilename)
		std::cout << "\nInput and output file cannot be the same!\nTry again: ";

	// We can get here by invalidating std::cin's state
	// We need an explicit check, because the two strings
	// can hold the same value in case that happened
	if (outfilename == infilename)
		throw std::runtime_error{"same file for input and output"};

	std::ofstream ofs{outfilename};
	if (!ofs)
		throw std::runtime_error{"can't open file: " + outfilename};

	print_lowercase(ifs, ofs);
}
