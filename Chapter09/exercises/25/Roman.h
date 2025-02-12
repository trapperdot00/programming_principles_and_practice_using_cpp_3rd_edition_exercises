#ifndef ROMAN_H
#define ROMAN_H

#include <string>
#include <vector>
#include <map>
#include <stdexcept>
#include <cctype>
#include <iostream>
#include <array>
#include <utility>

// Convert a single Roman digit to int
int roman_digit_to_int(char);

// Convert a sequence of Roman digits to ints
std::vector<int> roman_digits_to_ints(std::string);

// Checks whether a given Roman digit is legal
// when repeated a given amount of times
bool valid_roman_digit_repetition(char, size_t);

// Converts a given Roman number to its int equivalent
// Only allows unambiguous forms (e.g. "IX" instead of "VIIII")
// Throws when ambiguity is detected
// Range: 1-3999 inclusive
// Uses "IV" for 4, not "IIII"
// 'I', 'X', 'C', 'M' can be repeated 3 times,
// 'V', 'L', 'D' only once
int roman_to_int(const std::string&);

// Convert an integer to Roman numerals
// Range: 1-3999 inclusive
std::string int_to_roman(int);

// Checks whether two Roman digits can be subtracted from each other
bool roman_subtractable(int, int);

// Checks if given integer is the equivalent
// of the Roman numeral 'V', 'L', or 'D'
// Helps with the length of a condition inside roman_to_int
bool is_fivers(int val);

class Roman {
public:
	Roman(int i) : val(i) {
		check_range(val);
	}
	Roman(const std::string& s) : val(roman_to_int(s)) {}
	Roman& operator=(int rhs) {
		check_range(rhs);
		return *this;
	}
	Roman& operator=(const std::string& rhs) {
		val = roman_to_int(rhs);
		return *this;
	}
	int as_int() const { return val; }
private:
	static bool in_range(int);
	// Check and throw is int is out of range
	static void check_range(int);

	int val;
};

// Input and output as Roman numerals
// Converts to and from the integer value held by Roman
std::istream& operator>>(std::istream&, Roman&);
std::ostream& operator<<(std::ostream&, const Roman&);

#endif
