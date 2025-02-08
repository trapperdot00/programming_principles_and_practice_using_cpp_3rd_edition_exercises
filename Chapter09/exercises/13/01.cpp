#include <string_view>
#include <cctype>
#include <iostream>
#include <iomanip>
#include <map>
#include <array>
#include <fstream>
#include <sstream>

enum class Classification {
	space, alpha, digit, xdigit,
	upper, lower, alnum, cntrl,
	punct, print, graph, blank
};

int to_int(Classification c) {
	return static_cast<int>(c);
}

// Constructs a Classification with a range-checked int
Classification int_to_classification(int i) {
	if (i < to_int(Classification::space) ||
		to_int(Classification::blank) < i)
		throw std::runtime_error{"classification out-of-range"};
	return Classification{i};
}

// Converts a Classification to a human-readable,
// printable representation
std::string_view representation(Classification c) {
	constexpr static std::array<std::string_view, 12> table = {
		"Whitespace", "Alphabetic", "Digit", "Hexadecimal Digit",
		"Uppercase", "Lowercase", "Alphanumeric", "Control",
		"Punctuation", "Printable", "Graph", "Blank"
	};
	return table[to_int(c)];
}

// Bruteforce way of counting:
// relying on the fact that STL containers default initialize
// built-in types to 0
std::map<Classification, size_t> count_classifications(const std::string& s) {
	std::map<Classification, size_t> classifications;
	std::istringstream is{s};
	for (char ch = 0; is.get(ch); ) {
		if (std::isspace(ch))
			++classifications[Classification::space];
		if (std::isalpha(ch))
			++classifications[Classification::alpha];
		if (std::isdigit(ch))
			++classifications[Classification::digit];
		if (std::isxdigit(ch))
			++classifications[Classification::xdigit];
		if (std::isupper(ch))
			++classifications[Classification::upper];
		if (std::islower(ch))
			++classifications[Classification::lower];
		if (std::isalnum(ch))
			++classifications[Classification::alnum];
		if (std::iscntrl(ch))
			++classifications[Classification::cntrl];
		if (std::ispunct(ch))
			++classifications[Classification::punct];
		if (std::isprint(ch))
			++classifications[Classification::print];
		if (std::isgraph(ch))
			++classifications[Classification::graph];
		if (std::isblank(ch))
			++classifications[Classification::blank];
	}
	return classifications;
}

// Read exact contents of file into a string
std::string read_file(const std::string& filename) {
	std::ifstream ifs{filename};
	if (!ifs)
		throw std::runtime_error{"can't open " + filename + " for reading"};
	std::string contents;
	for (char ch = 0; ifs.get(ch); ) {
		contents += ch;
	}
	return contents;
}

// Print count of classifications for a string
std::ostream& print_classifications(std::ostream& os, const std::string& s) {
	const std::map<Classification, size_t> data = count_classifications(s);
	for (int i = 0; i <= to_int(Classification::blank); ++i) {
		Classification c = int_to_classification(i);
		os << std::setw(18) << std::left << representation(c) << std::setw(10);

		// Only try to access the value of the given key, if it exists,
		// if it doesn't exists, print 0
		std::map<Classification, size_t>::const_iterator it = data.find(c);
		if (it != data.cend())
			os << data.at(c);
		else
			os << 0;
		os << '\n';
	}
	return os;
}

int main() {
	std::cout << "Enter filename: ";
	std::string filename;
	if (!(std::cin >> filename))
		throw std::runtime_error{"no data"};
	print_classifications(std::cout, read_file(filename));
}
