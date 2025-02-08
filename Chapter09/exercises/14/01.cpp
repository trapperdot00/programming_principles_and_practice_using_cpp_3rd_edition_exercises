#include <fstream>
#include <format>
#include <iostream>
#include <vector>
#include <string>

// Read numbers from a given input stream
std::vector<double> read_numbers(std::istream& is) {
	std::vector<double> numbers;
	for (double d; is >> d; )
		numbers.push_back(d);
	return numbers;
}

// Read numbers from a file with a given filename
std::vector<double> read_numbers(const std::string& filename) {
	std::ifstream ifs{filename};
	if (!ifs)
		throw std::runtime_error{"can't open " + filename + " for reading"};
	return read_numbers(ifs);
}

// Print numbers into a given output stream, formatted:
// left-aligned numbers with 20 width and 8 precision in scientific notation,
// in 4 colums
std::ostream& print_numbers
(std::ostream& os, const std::vector<double>& numbers) {
	constexpr size_t column_count = 4;
	for (size_t i = 0; i < numbers.size(); ++i) {
		// Append a newline
		if (i && i % column_count == 0)
			os << '\n';
		os << std::format("{:<20.8e}", numbers[i]);
	}
	return os;
}

// Print numbers into a file with a given filename,
// doesn't return the output stream because it would be
// a reference to a local object
// Prints a newline after the numbers
void print_numbers
(const std::string& filename, const std::vector<double>& numbers) {
	std::ofstream ofs{filename};
	if (!ofs)
		throw std::runtime_error{"can't open " + filename + " for writing"};
	print_numbers(ofs, numbers) << '\n';
}

int main() {
	std::cout << "Enter input filename: ";
	std::string infilename;
	if (!(std::cin >> infilename))
		throw std::runtime_error{"no data"};

	std::cout << "Enter output filename: ";
	std::string outfilename;
	if (!(std::cin >> outfilename))
		throw std::runtime_error{"no data"};

	print_numbers(outfilename, read_numbers(infilename));
}
