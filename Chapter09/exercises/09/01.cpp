#include <vector>
#include <string>
#include <sstream>
#include <iostream>
#include <utility>

// Create a vector of whitespace-separated substrings
std::vector<std::string> split(const std::string& s) {
	std::vector<std::string> substrings;
	std::istringstream is{s};
	for (std::string substring; is >> substring; ) {
		substrings.push_back(std::move(substring));
	}
	return substrings;
}

// Read a line, then output its substrings
std::ostream& program_loop(std::istream& is, std::ostream& os) {
	os << "Enter line: ";
	if (std::string line; std::getline(is, line)) {
		std::vector<std::string> substrings = split(line);
		if (!substrings.empty())
			os << "\nSubstrings:\n";
		for (const std::string& sub : substrings)
			os << sub << '\n';
	}
	return os;
}

int main() {
	do {
		program_loop(std::cin, std::cout) << '\n';
	} while (std::cin);
}
