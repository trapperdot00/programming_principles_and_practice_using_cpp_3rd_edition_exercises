#include <fstream>
#include <iostream>
#include <string>
#include <stdexcept>

std::ostream& print_lines(std::ostream& os, std::istream& is) {
	for (std::string line; std::getline(is, line); )
		os << line << '\n';
	return os;
}

void concatenate
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
	print_lines(ofs, ifs1);
	print_lines(ofs, ifs2);
}

int main() {
	std::cout << "Enter first input file:\n";
	std::string file1;
	if (!(std::cin >> file1))
		throw std::runtime_error{"no data"};

	std::cout << "Enter second input file:\n";
	std::string file2;
	if (!(std::cin >> file2))
		throw std::runtime_error{"no data"};

	std::cout << "Enter output file:\n";
	std::string outfile;
	if (!(std::cin >> outfile))
		throw std::runtime_error{"no data"};

	concatenate(file1, file2, outfile);
}
