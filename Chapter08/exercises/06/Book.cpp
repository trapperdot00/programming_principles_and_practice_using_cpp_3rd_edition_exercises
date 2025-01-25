#include "Book.h"

bool Book::valid_isbn(const std::string& s) const {
	// Check minimum length (n-n-n-x)
	if (s.size() < 7)
		return false;
	size_t index = 0;	// Index to subscript ISBN
	// Process n-n-n- : integers followed by a dash three times
	for (int i = 0; i < 3; ++i) {
		bool has_digit = false;
		// Skip digits
		while (index < s.size() && std::isdigit(s[index])) {
			has_digit = true;
			++index;
		}
		if (s[index++] != '-')
			return false;
		if (!has_digit)
			return false;
	}
	// Process last digit or letter
	if (index == s.size() - 1 && std::isalnum(s[index]))
		return true;
	return false;
}

bool operator==(const Book& lhs, const Book& rhs) {
	return lhs.isbn() == rhs.isbn();
}

bool operator!=(const Book& lhs, const Book& rhs) {
	return !(lhs == rhs);
}

std::ostream& operator<<(std::ostream& os, const Book& b) {
	return os << b.title() << '\n'
		<< b.author() << '\n'
		<< b.isbn();
}
