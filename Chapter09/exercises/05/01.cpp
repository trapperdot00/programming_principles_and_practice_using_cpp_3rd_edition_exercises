#include <cctype>
#include <string>
#include <iostream>

// Print every classification
// that applies to character
std::ostream& print_classifications(std::ostream& os, char c) {
	os << c;
	if (isspace(c))
		os << " isspace";
	if (isalpha(c))
		os << " isalpha";
	if (isdigit(c))
		os << " isdigit";
	if (isxdigit(c))
		os << " isxdigit";
	if (isupper(c))
		os << " isupper";
	if (islower(c))
		os << " islower";
	if (isalnum(c))
		os << " isalnum";
	if (iscntrl(c))
		os << " iscntrl";
	if (ispunct(c))
		os << " ispunct";
	if (isprint(c))
		os << " isprint";
	if (isgraph(c))
		os << " isgraph";
	return os;
}

// Print every classification
// for every character in the string
std::ostream& print_classifications(std::ostream& os, const std::string& s) {
	for (char c : s)
		print_classifications(os, c) << '\n';
	return os;
}

int main() {
	// Read strings and print their characters' classifications
	for (std::string s; std::cin >> s; ) {
		print_classifications(std::cout, s);
	}
}
