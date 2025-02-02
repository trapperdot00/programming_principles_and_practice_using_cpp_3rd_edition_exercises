#include <string>
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <sstream>
#include <format>

// Iterate through words in a string and check
// for match for given and current word
bool contains_word(const std::string& line, const std::string& word) {
	std::istringstream stream{line};
	for (std::string s; stream >> s; )
		if (s == word)
			return true;
	return false;
}

// Iterate through istream's data line-by-line,
// print line if it contains the passed word
void print_word_lines(std::istream& is, const std::string& word) {
	// Width for the line number field
	constexpr size_t line_width = 5;
	size_t line_count = 0;
	for (std::string line; std::getline(is, line); ++line_count)
		if (contains_word(line, word)) {
			if (line_count == 0)
				std::cout << "\nOccurences:\n";
			std::cout << std::format("line {:<{}} | {}\n", line_count+1, line_width, line);
		}
}

int main() {
	std::cout << "Enter filename: ";
	std::string filename;
	std::cin >> filename;
	std::ifstream ifs{filename};
	if (!ifs)
		throw std::runtime_error{"can't open file: " + filename};

	std::cout << "Enter word to look for: ";
	std::string word;
	if (!(std::cin >> word))
		throw std::runtime_error{"no data for word"};

	print_word_lines(ifs, word);
}
