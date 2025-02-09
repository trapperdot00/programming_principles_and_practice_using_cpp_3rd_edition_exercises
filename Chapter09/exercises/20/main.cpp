#include "Year.h"

#include <fstream>

int main() {
	std::cout << "Please enter input file name\n";
	std::string iname;
	std::cin >> iname;
	std::ifstream ifs{iname};
	if (!ifs)
		throw std::runtime_error{"can't open input file " + iname};

	ifs.exceptions(ifs.exceptions() | std::ios::badbit);

	std::cout << "Please enter output file name\n";
	std::string oname;
	std::cin >> oname;
	std::ofstream ofs{oname};
	if (!ofs)
		throw std::runtime_error{"can't open output file " + oname};

	std::vector<Year> ys;
	while (true) {
		Year y;
		if (!(ifs >> y))
			break;
		ys.push_back(y);
	}
	std::cout << "read " << ys.size() << " years of readings\n";

	for (const Year& y : ys)
		print_year(ofs, y);
}
