#include <fstream>
#include <iostream>
#include <string>
#include <stdexcept>

// Print that sets the given boolean value when it succeeds,
// inserts space before printing if bool is already set
void loop_print(std::ostream& os, const std::string& s, bool& b) {
	if (os << (b ? " " : "") << s)
		b = true;
}

// Takes two input streams with sorted elements,
// writes both input stream's elements in sorted order
// to the given output stream
std::ostream& merge(std::istream& is1, std::istream& is2, std::ostream& os) {
	// To insert space between words
	bool has_written = false;
	std::string s1;
	std::string s2;
	is1 >> s1;
	is2 >> s2;
	while (is1 && is2) {
		if (s1 < s2) {
			loop_print(os, s1, has_written);
			is1 >> s1;
		} else {
			loop_print(os, s2, has_written);
			is2 >> s2;
		}
	}
	while (is1) {
		loop_print(os, s1, has_written);
		is1 >> s1;
	}
	while (is2) {
		loop_print(os, s2, has_written);
		is2 >> s2;
	}
	return os;
}

// Merge using temporarily constructed file streams
void merge
(const std::string& in1, const std::string& in2, const std::string& out) {
	std::ifstream ifs1{in1};
	if (!ifs1)
		throw std::runtime_error{"can't open " + in1 + " for reading"};
	std::ifstream ifs2{in2};
	if (!ifs2)
		throw std::runtime_error{"can't open " + in2 + " for reading"};
	std::ofstream ofs{out};
	if (!ofs)
		throw std::runtime_error{"can't open " + out + " for writing"};
	
	merge(ifs1, ifs2, ofs) << '\n';
}

// Checks if given file is sorted
bool sorted(const std::string& filename) {
	std::ifstream ifs{filename};
	if (!ifs)
		throw std::runtime_error{"can't open " + filename + " for reading"};
	std::string prev;
	std::string curr;
	while (ifs >> curr) {
		if (!prev.empty() && prev > curr)
			return false;
		prev = curr;
	}
	return true;
}

int main() {
	std::cout << "Enter first input file:\n";
	std::string infile1;
	if (!(std::cin >> infile1))
		throw std::runtime_error{"no data"};

	std::cout << "Enter second input file:\n";
	std::string infile2;
	if (!(std::cin >> infile2))
		throw std::runtime_error{"no data"};
	
	std::cout << "Enter output file:\n";
	std::string outfile;
	if (!(std::cin >> outfile))
		throw std::runtime_error{"no data"};

	merge(infile1, infile2, outfile);

	// Check if output file is sorted, if it isn't then the user
	// likely provided wrongly sorted files
	if (!sorted(outfile))
		throw std::runtime_error{"error in input file sorting"};
}
