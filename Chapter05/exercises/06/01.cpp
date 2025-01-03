#include <vector>
#include <iostream>
#include <random>
#include <algorithm>

class read_error{};
class digit_size_error{};
class unique_error{};

std::default_random_engine& get_random() {
	static std::default_random_engine e;
	return e;
}
void seed(size_t n) {
	get_random().seed(n);
}

template <typename T>
bool contains(const std::vector<T>& vec, const T& e) {
	for (typename std::vector<T>::const_iterator it = vec.cbegin();
			it != vec.cend(); ++it) {
		if (*it == e)
			return true;
	}
	return false;
}

std::vector<char> random_chars(size_t n) {
	static std::uniform_int_distribution<char> d('a', 'z');
	std::vector<char> vec;
	while (vec.size() < n) {
		char rand = d(get_random());
		if (!contains(vec, rand))
			vec.push_back(rand);	
	}
	return vec;
}

bool is_unique(std::string s) {
	std::ranges::sort(s);
	for (size_t i = 1; i < s.size(); ++i)
		if (s[i-1] == s[i])
			return false;
	return true;
}

size_t bulls(const std::vector<char>& vec, const std::string& s) {
	size_t b = 0;
	for (size_t i = 0; i < vec.size(); ++i)
		if (vec[i] == s[i])
			++b;
	return b;
}
size_t cows(const std::vector<char>& vec, const std::string& s) {
	size_t c = 0;
	for (size_t i = 0; i < vec.size(); ++i) {
		for (size_t j = 0; j < s.size(); ++j) {
			if (i != j && vec[i] == s[j])
				++c;
		}
	}
	return c;
}

void print_status(size_t b, size_t c) {
	std::cout << b << (b == 1 ? " bull" : " bulls") << " and "
		<< c << (c == 1 ? " cow" : " cows") << '\n';
}

template <typename T>
T read() {
	T t;
	if (!(std::cin >> t))
		throw read_error{};
	return t;
}

int main()
try {
	constexpr size_t letter_count = 4;
	std::cout << "Bulls and Cows.\nGuess " << letter_count << " letters!\n\n";
	std::cout << "Enter seed: ";
	seed(read<size_t>());
	while (true) {
		const std::vector<char> letters = random_chars(letter_count);
		bool won = false;
	
		while (!won) try {
			std::cout << "Enter " << letter_count << " letters: ";
			std::string guess = read<std::string>();
			if (guess.size() != letter_count)
				throw digit_size_error{};
			if (!is_unique(guess))
				throw unique_error{};
			size_t bulls_cnt = bulls(letters, guess);
			if (bulls_cnt == letter_count) {
				std::cout << "You correctly guessed all characters!\n\nNew Game.\n";
				won = true;
			} else {
				size_t cows_cnt = cows(letters, guess);
				print_status(bulls_cnt, cows_cnt);
			}
		} catch (digit_size_error& e) {
			std::cerr << "Enter " << letter_count << " digits!\n";
		} catch (unique_error& e) {
			std::cerr << "Only unique characters allowed!\n";
		}
	}
} catch (read_error& e) {
	std::cerr << "Goodbye!\n";
}
