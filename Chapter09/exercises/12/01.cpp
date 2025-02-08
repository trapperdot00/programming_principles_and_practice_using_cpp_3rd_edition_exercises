#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
#include <utility>
#include <iostream>
#include <stdexcept>

// Read contents of file, separate words into separate elements in a vector
std::vector<std::string> read_words_of_file(const std::string& filename) {
	std::ifstream ifs{filename};
	if (!ifs)
		throw std::runtime_error{"can't open " + filename + " for reading"};
	std::vector<std::string> words;
	for (std::string word; ifs >> word; )
		words.push_back(std::move(word));
	return words;
}

// Write each word into a file with a given filename,
// deleting its contents before writing into it
// The words are separated by spaces, the file is ended with a newline
void write_words_to_file
(const std::string& filename, const std::vector<std::string>& words) {
	std::ofstream ofs{filename};
	for (size_t i = 0; i < words.size(); ++i) {
		if (i)
			ofs << ' ';
		ofs << words[i];
	}
	ofs << '\n';
}

void reverse_words_of_file(const std::string& filename) {
	std::vector<std::string> words = read_words_of_file(filename);
	std::ranges::reverse(words);
	write_words_to_file(filename, words);
}

int main() {
	std::cout << "Enter name of file to reverse its order of words: ";
	std::string filename;
	if (!(std::cin >> filename))
		throw std::runtime_error{"no data"};
	reverse_words_of_file(filename);
}
