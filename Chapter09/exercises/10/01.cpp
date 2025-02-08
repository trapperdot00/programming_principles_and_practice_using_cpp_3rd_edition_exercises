#include <vector>
#include <string>
#include <sstream>
#include <iostream>
#include <utility>
#include <cctype>

// A separator is whitespace or a character in the given string
bool is_separator(char c, const std::string& w) {
	return std::isspace(c) || w.find(c) != std::string::npos;
}

// Reads a string until encountering a separator character
std::string read_substring(std::istream& is, const std::string& w) {
	std::string substring;
	for (char ch = 0; is.get(ch) && !is_separator(ch, w); ) {
		substring += ch;
	}
	return substring;
}

// Reads substrings into separate elements in a vector
std::vector<std::string> split(const std::string& s, const std::string& w) {
	std::vector<std::string> substrings;
	std::istringstream is{s};
	while (is) {
		std::string substring = read_substring(is, w);
		if (!substring.empty())
			substrings.push_back(std::move(substring));
	}
	return substrings;
}

// Interact with the user
std::ostream& interact(std::istream& is, std::ostream& os, const std::string& w) {
	os << "Enter line: ";
	std::string line;
	if (std::getline(is, line)) {
		std::vector<std::string> substrings = split(line, w);
		if (!substrings.empty())
			os << "\nSubstrings:\n";
		for (const std::string& substring : substrings)
			os << substring << '\n';
	}
	return os;
}

int main() {
	std::cout << "Enter separators: ";
	std::string sep;
	if (std::cin >> sep) {
		// Ignore separators line to avoid getline
		// from reading an empty line in interact
		std::cin.ignore();
		do {
			interact(std::cin, std::cout, sep) << '\n';
		} while (std::cin);
	}
}
