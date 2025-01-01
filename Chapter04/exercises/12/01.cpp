#include <iostream>
#include <vector>
#include <string>
#include <cstddef>

class digit_error{};	// mismatched digit sizes
class char_error{};		// for invalid characters given
class read_error{};		// for no input

int get_digit_size(int num) {
	int size = 1;
	while (num /= 10)
		++size;
	return size;
}

std::vector<int> convert_n(const std::string& s, size_t n) {
	std::vector<int> vec;
	for (size_t i = 0; i < s.size() && i < n; ++i) {
		if (s[i] < '0' || s[i] > '9')
			throw char_error{};
		vec.push_back(s[i] - '0');
	}
	return vec;
}

// Correct digits in the correct positions
int bulls(const std::vector<int>& digits, const std::vector<int>& guess) {
	if (digits.size() != guess.size())
		throw digit_error{};
	int b = 0;
	for (std::vector<int>::size_type i = 0; i != digits.size(); ++i)
		if (digits[i] == guess[i])
			++b;
	return b;
}

// Correct digits in the wrong positions
int cows(const std::vector<int>& digits, const std::vector<int>& guess) {
	if (digits.size() != guess.size())
		throw digit_error{};
	int c = 0;
	for (std::vector<int>::size_type i = 0; i < guess.size(); ++i) {
		for (std::vector<int>::size_type j = 0; j < digits.size(); ++j) {
			if (i != j && guess[i] == digits[j]) {
				++c;
				break;
			}
		}
	}
	return c;
}

int main()
try {
	const std::vector<int> digits = {1,2,3,4};
	bool game_in_progress = true;
	while (game_in_progress) {
		try {
			std::cout << "Enter " << digits.size() << " digits: ";
			std::string s;
			if (!(std::cin >> s))
				throw read_error{};
			std::vector<int> guess = convert_n(s, digits.size());
			size_t b = bulls(digits, guess);
			if (b == digits.size()) {
				std::cout << "\nYou correctly guessed the digits!\n";
				game_in_progress = false;
			} else {
				size_t c = cows(digits, guess);
				std::cout << b << (b == 1 ? " bull" : " bulls") << " and "
					<< c << (c == 1 ? " cow" : " cows") << "\n\n";
			}
		} catch (digit_error& e) {
			std::cerr << "Invalid digit size!\nRequired digits: " << digits.size() << "\nTry again!\n\n";
		} catch (char_error& e) {
			std::cerr << "Invalid character!\nTry again!\n\n";
		}
	}
} catch (read_error& e) {
	std::cerr << "\nGoodbye!\n";
}
