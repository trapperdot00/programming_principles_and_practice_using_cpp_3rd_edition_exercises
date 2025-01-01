#include <iostream>
#include <vector>
#include <string>
#include <cstddef>
#include <random>
#include <algorithm>

class init_digit_error{};	// invalid initializing digit count
class size_error{};		// mismatched digit sizes
class uniqueness_error{};	// digits not unique
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

bool contains(const std::vector<int>& vec, int num) {
	if (vec.empty())
		return false;
	std::vector<int>::size_type i = 0;
	while (i < vec.size() && vec[i] != num) {
		++i;
	}
	return i != vec.size();
}

// Correct digits in the correct positions
int bulls(const std::vector<int>& digits, const std::vector<int>& guess) {
	int b = 0;
	for (std::vector<int>::size_type i = 0; i != digits.size(); ++i)
		if (digits[i] == guess[i])
			++b;
	return b;
}

// Correct digits in the wrong positions
int cows(const std::vector<int>& digits, const std::vector<int>& guess) {
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

std::default_random_engine& get_random() {
	static std::default_random_engine e;
	return e;
}
void seed(size_t n) {
	get_random().seed(n);
}

std::vector<int> random_digits(size_t n) {
	static std::uniform_int_distribution<char> u('0', '9');
	if (!n || n > 9)
		throw init_digit_error{};
	std::vector<int> digits;
	for (size_t i = 0; i < n; ++i) {
		char rand = ' ';
		do {
			rand = u(get_random());
		} while (contains(digits, rand - '0'));
		digits.push_back(rand - '0');
	}
	return digits;
}

std::string plural(const std::string& s, size_t cnt, const std::string& suffix) {
	return cnt == 1 ? s : s + suffix;
}

void print(size_t b, size_t c) {
	std::cout << b << plural(" bull", b, "s") << " and "
		<< c << plural(" cow", c, "s") << "\n\n";
}

template <typename T>
T read_input() {
	T val;
	if (!(std::cin >> val))
		throw read_error{};
	return val;
}

void check_size(const std::string &s, size_t n) {
	if (s.size() != n)
		throw size_error{};
}

void check_unique(std::string s) {
	std::ranges::sort(s);
	for (size_t i = 1; i < s.size(); ++i) {
		if (s[i-1] == s[i])
			throw uniqueness_error{};
	}
}

int main()
try {
	constexpr size_t digit_count = 4;

	std::cout << "Enter seed: ";
	seed(read_input<size_t>());	
	do {	// Game loop terminated by an exception, such as reading EOF
		const std::vector<int> digits = random_digits(digit_count);	// Digits to guess
		bool won = false;
		do try {	// Round loop
			std::cout << "Enter " << digit_count << " digits: ";
			std::string s = read_input<std::string>();
			check_size(s, digit_count);
			check_unique(s);
			const std::vector<int> guess = convert_n(s, digit_count);
			size_t bulls_count = bulls(digits, guess);

			// Check for not winning
			if (bulls_count != digit_count) {
				size_t cows_count = cows(digits, guess);
				print(bulls_count, cows_count);
			} else {
				// Won
				std::cout << "You correctly guessed the digits!\n";
				won = true;
			}
		} catch (uniqueness_error& e) {
			std::cerr << "Only unique digits allowed!\n";
		} catch (size_error& e) {
			std::cerr << "Invalid digit size! (Required digits: " << digit_count << ")\n";
		} catch (char_error& e) {
			std::cerr << "Invalid character!\n";
		} while (!won);
		std::cout << "\n\nNew game:\n";
	} while (1);

} catch (init_digit_error& e) {
	std::cerr << "Invalid starting digits, exiting!\n";
} catch (read_error& e) {
	std::cerr << "\nGoodbye!\n";
}
