#include <iostream>
#include <cctype>
#include <vector>
#include <string>
#include <sstream>
#include <iomanip>

// To keep track of the original base of a number
enum class NumBase {
	dec, oct, hex
};

struct Number {
	int value;		// Decimal value
	NumBase base;	// Base the value was originally read in
};

// Return whether a character is a digit of the octal numeral system
bool isoctal(char c) {
	return c >= '0' && c <= '7';
}

// Check whether the next read character from
// a given istream is equal to a character given,
// if yes, consume the character,
// else put the read character back to the stream
bool read_exact(std::istream& is, char c) {
	if (char ch = 0; is.get(ch) && ch == c)
		return true;
	is.unget();
	return false;
}

// Parse a number read from a given stream:
//  - if the characters "0x" can be read: hexadecimal
//  - if a '0' and an octal character can be read: octal
//  - otherwise it is decimal
// The number is left in the stream to read.
// Applies a manipulator to the stream and returns a
// NumBase to indicate the read number's base and which
// manipulator has been set to correctly read the number.
NumBase handle_base(std::istream& is) {
	NumBase base = NumBase::dec;
	char ch = 0;

	// Read a character
	if (!is.get(ch))
		return base;

	// Assume that every character sequence not starting with '0' is decimal,
	// actual reading will determine whether the value is numeric
	if (ch != '0') {
		is.unget();
		return base;
	}
	// --- Here we have correctly read a '0' ---
	
	// Read next character without removing it from the stream
	ch = is.peek();

	// '0' and nothing follows it: decimal
	if (ch == EOF) {
		is.unget();
		return base;
	}

	// "0x": hexadecimal
	if (ch == 'x') {
		base = NumBase::hex;
		is >> std::hex;
		// Skip 'x'
		is.ignore();
	}
	// '0' and the next character is octal: octal
	else if (isoctal(ch)) {
		base = NumBase::oct;
		is >> std::oct;
	}
	// '0' and something follows it:
	// we can read at least a zero now with >>,
	// any invalid characters following it will be ignored
	else
		is.unget();
	return base;
}

std::istream& operator>>(std::istream& is, Number& r) {
	// Read next word to parse
	std::string word;
	is >> word;
	// Create istream from word
	std::istringstream istr(word);

	// These two function calls should be in this exact order!
	
	// Read next character, if it is '-', consume it, returns true,
	// if it isn't, put it back into the stream and return false
	bool negative = read_exact(istr, '-');
	// Determine base from the now stripped-from-sign number
	NumBase base = handle_base(istr);

	// Read the number with the correct base manipulator set
	int value = 0;
	if (!(istr >> value)) {
		// If the reading failed from the istringstream,
		// also set failbit on the istream to indicate
		// error to the user
		is.clear(std::ios::failbit);
		return is;
	}
	// Change object only if reading succeeded
	r = Number{negative ? -value : value, base};
	return is;
}

// Returns the octal representation of a decimal number
// with a '0' prefix
std::string octal(int n) {
	std::ostringstream ret;
	ret << std::oct << '0' << n;
	return ret.str();
}

// Returns the hexadecimal representation of a decimal number
// with a "0x" prefix
std::string hexadecimal(int n) {
	std::ostringstream ret;
	ret << std::hex << "0x" << n;
	return ret.str();
}

// Returns number of characters required to print
// representation of number in a given numeral base
size_t length(int n, NumBase base = NumBase::dec) {
	std::ostringstream ret;
	switch (base) {
	case NumBase::oct:
		ret << octal(n);
		break;
	case NumBase::hex:
		ret << hexadecimal(n);
		break;
	default:
		ret << n;
		break;
	}
	return ret.str().size();
}

// Returns the maximum length of numbers
// in their corresponding base representations
size_t maxwidth_bases(const std::vector<Number>& vec) {
	size_t ret = 0;
	for (size_t i = 0; i < vec.size(); ++i) {
		size_t curr_length = length(vec[i].value, vec[i].base);
		if (!i)
			ret = curr_length;
		else if (ret < curr_length)
			ret = curr_length;
	}
	return ret;
}

// Returns the maximum length of numbers
// in decimal representation
size_t maxwidth_dec(const std::vector<Number>& vec) {
	size_t ret = 0;
	for (size_t i = 0; i < vec.size(); ++i) {
		size_t curr_length = length(vec[i].value);
		if (!i)
			ret = curr_length;
		else if (ret < curr_length)
			ret = curr_length;
	}
	return ret;
}

int main() {
	// Container to hold decimal numbers with context
	// of their default numeral bases they were read in
	std::vector<Number> numbers;

	// Input loop until invalid input
	for (Number n; std::cin >> n; ) {
		numbers.push_back(n);
	}

	// Amount to add to every field's width
	constexpr size_t excess = 2;

	// Width of originally inputted number's field
	const size_t original_width = maxwidth_bases(numbers) + excess;
	
	// Width of base representation field
	constexpr size_t base_width = 11 + excess;
	
	// Width of "converts to" field
	constexpr size_t convert_width = 11 + excess;
	
	// Width of decimal number field
	const size_t number_width = maxwidth_dec(numbers) + excess;

	// Width of "decimal" field
	constexpr size_t decimal_width = 7 + excess;

	// Print formatted output:
	//  - originally inputted number
	//  - original base
	//  - value in decimal
	for (const Number& n : numbers) {
		switch (n.base) {
		case NumBase::dec:
			std::cout << std::setw(original_width)
				<< std::left << n.value
				<< std::setw(base_width) << "decimal"
				<< std::setw(convert_width) << "converts to"
				<< std::setw(number_width) << n.value
				<< std::setw(decimal_width) << "decimal"
				<< '\n';
			break;
		case NumBase::oct:
			std::cout << std::setw(original_width)
				<< std::left << octal(n.value)
				<< std::setw(base_width) << "octal"
				<< std::setw(convert_width) << "converts to"
				<< std::setw(number_width) << n.value
				<< std::setw(decimal_width) << "decimal"
				<< '\n';
			break;
		case NumBase::hex:
			std::cout << std::setw(original_width)
				<< std::left << hexadecimal(n.value)
				<< std::setw(base_width) << "hexadecimal"
				<< std::setw(convert_width) << "converts to"
				<< std::setw(number_width) << n.value
				<< std::setw(decimal_width) << "decimal"
				<< '\n';
			break;
		}
	}	
}
