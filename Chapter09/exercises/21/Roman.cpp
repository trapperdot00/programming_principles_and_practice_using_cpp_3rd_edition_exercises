#include "Roman.h"

int roman_digit_to_int(char c) {
	static const std::map<char, int> digits = {
		{'I', 1}, {'V', 5}, {'X', 10},
		{'L', 50}, {'C', 100}, {'D', 500},
		{'M', 1000}	
	};
	c = std::toupper(c);
	auto it = digits.find(c);
	if (it == digits.cend())
		throw std::runtime_error{"invalid character in Roman number"};
	return it->second;
}

std::vector<int> roman_digits_to_ints(std::string s) {
	if (s.empty())
		throw std::runtime_error{"empty string as Roman number"};
	std::vector<int> values;
	for (char c : s)
		values.push_back(roman_digit_to_int(c));
	return values;
}

bool valid_roman_digit_repetition(char digit, size_t count) {
	static const std::map<int, size_t> repeats = {
		{1, 3}, {5, 1}, {10, 3},
		{50, 1}, {100, 3}, {500, 1},
		{1000, 3}
	};
	int value = roman_digit_to_int(digit);
	return count <= repeats.find(value)->second;
}

int roman_to_int(const std::string& s) {
	// Values for each digit
	// Deals with empty string and illegal characters
	// Case-insensitive checking (converts characters to uppercase)
	const std::vector<int> digit_values = roman_digits_to_ints(s);

	int value = 0;				// Accumulates the digits' values
	int prev = 0;				// Previous value
	int prev_prev = 0;			// Value before the previous one
	enum Operation { addition, subtraction } prev_operation{addition};
	int prev_subtracted = 0;	// Value that has been previously subtracted
	size_t repetition = 0;		// Repetition counter for current digit
	
	for (size_t i = 0; i < digit_values.size(); ++i) {
		// Shorthand for current digit value
		int curr = digit_values[i];

		// Adjust and check repetition count
		repetition = (i == 0 || prev == curr) ? repetition + 1 : 1;
		if (!valid_roman_digit_repetition(s[i], repetition))
			throw std::runtime_error{"repetition error"};

		if (i == 0) {
			value = curr;
		} else if (prev >= curr) {
			// Prevent adding already subtracted digit: "IXI", "IVI", "CMC"
			if (prev_subtracted == curr)
				throw std::runtime_error{"ambiguity"};
			// Prevent adding subtracted-from digit: "IVV", "IXX", "CMM"
			if (prev_operation == subtraction && prev == curr)
				throw std::runtime_error{"wrong order"};
			value += curr;
			prev_operation = addition;
		} else if (prev_operation == addition && roman_subtractable(prev, curr)) {
			// Prevent other ambiguous forms: "IIV", "IIX", "CCM"; "VIV", "LXL", "DCD"
			if (prev_prev == prev || (is_fivers(curr) && prev_prev == curr))
				throw std::runtime_error{"ambiguity"};
			value += curr - 2 * prev;		// Subtract already added prev
			prev_operation = subtraction;
			prev_subtracted = prev;
		} else {
			// Prevent other uncaught illegal forms: "IC", "IL", "IM", "VL", "VC"
			throw std::runtime_error{"subtraction error"};
		}
		prev_prev = prev;
		prev = curr;
	}
	// Check if result is in range
	if (value <= 0 || value >= 4000)
		throw std::runtime_error{"invalid value"};
	return value;
}

std::string int_to_roman(int i) {
	const static std::array<std::pair<int, std::string>, 13> conv_tbl = {{
		{1, "I"}, {4, "IV"}, {5, "V"}, {9, "IX"}, {10, "X"},
		{40, "XL"}, {50, "L"}, {90, "XC"}, {100, "C"},
		{400, "CD"}, {500, "D"}, {900, "CM"}, {1000, "M"}
	}};
	if (i < 1 || 3999 < i)
		throw std::runtime_error{"out of range"};
	
	std::string roman;
	// Start iterator at the last element of the array:
	// Roman numbers start from the largest to the smallest digit
	auto it = conv_tbl.crbegin();
	while (i > 0) {
		int whole_part = i / it->first;
		// Modify i to be less than the currently denoted element in the array
		i %= it->first;
		// Append the right amount of the current digits
		while (whole_part-- > 0) {
			roman += it->second;
		}
		// Advance reverse iterator: will point to the previous element
		++it;
	}
	return roman;
}

bool roman_subtractable(int curr, int next) {
	if (curr == 1)
		return next == 5 || next == 10;
	if (curr == 10)
		return next == 50 || next == 100;
	if (curr == 100)
		return next == 500 || next == 1000;
	return false;
}

bool is_fivers(int val) {
	return val == 5 || val == 50 || val == 500;
}

bool Roman::in_range(int i) {
	return 0 < i && i < 4000;
}

void Roman::check_range(int i) {
	if (!in_range(i))
		throw std::runtime_error{"out of range"};
}

std::istream& operator>>(std::istream& is, Roman& rhs) {
	std::string s;
	if (is >> s) {
		rhs = s;
	}
	return is;
}

std::ostream& operator<<(std::ostream& os, const Roman& rhs) {
	return os << int_to_roman(rhs.as_int());
}
