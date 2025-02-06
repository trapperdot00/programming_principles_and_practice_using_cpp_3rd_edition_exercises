#include <iostream>
#include <string>
#include <array>
#include <stdexcept>

// Checks if a given character is a punctuation,
// where a punctuation character is defined by us:
// 	. ; , ? - '
// The Standard Library has even more punctuation characters,
// but the exercise explicitly specified which ones to change
bool is_mypunct(char c) {
	constexpr static std::array<char, 6> punctuation = {
		'.', ';', ',', '?', '-', '\''
	};
	for (char p : punctuation)
		if (c == p)
			return true;
	return false;
}

// Change a punctuation character to space
void punct_to_space(char &c) {
	if (is_mypunct(c))
		c = ' ';
}

// Modify strings using this rule:
//  - characters enclosed in double quotes '"' aren't modified
//  - punctuation characters (.;,?-') are replaced to spaces if not in double quotes
// Throws an error if a double quote sequence is not terminated
void modify(std::string& s) {
	// Keep track of quoted parts
	bool in_quote_part = false;
	for (char& c : s) {
		// Quote encountered, flip bool
		if (c == '"')
			in_quote_part = !in_quote_part;
		// Only modify char if not inside a double quote sequence
		if (!in_quote_part)
			punct_to_space(c);
	}
	// Double quote sequence is not terminated
	if (in_quote_part)
		throw std::runtime_error{"expected closing '\"'"};
}

int main() {
	// Read lines as it would be inconvenient to apply punctuation to singular words
	for (std::string s; std::getline(std::cin, s); ) {
		modify(s);
		std::cout << s << '\n';
	}
}
