#include "Point.h"

#include <string>
#include <fstream>

int main() {
	std::string fname;
	std::cout << "Enter input filename: ";
	std::cin >> fname;

	std::ifstream infile{fname};
	if (!infile)
		throw std::runtime_error{"Cannot open file"};

	for (Point p; infile >> p; ) {
		std::cout << p << '\n';
	}
}
