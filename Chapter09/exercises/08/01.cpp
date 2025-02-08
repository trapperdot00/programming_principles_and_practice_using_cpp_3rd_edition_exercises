/*	The previous (exercise07) program didn't remove
 *	parentheses and colons from the words,
 *	I added them into the punctuation list so that
 *	they will be removed
 */

#include <iostream>
#include <string>
#include <array>
#include <sstream>
#include <map>
#include <cctype>
#include <fstream>
#include <vector>
#include <algorithm>

// Checks if a given character is a punctuation,
// where a punctuation character is defined by us:
// 	. ; , ? - ' : ( )
// The Standard Library has even more punctuation characters,
// but the exercise explicitly specified which ones to change
bool is_mypunct(char c) {
	constexpr static std::array<char, 9> punctuation = {
		'.', ';', ',', '?', '-', '\'', ':', '(', ')'
	};
	for (char p : punctuation)
		if (c == p)
			return true;
	return false;
}

// Check if string consists of only whitespace
bool only_spaces(const std::string& s) {
	for (char c : s)
		if (!std::isspace(c))
			return false;
	return true;
}

std::string uncontract(const std::string& s) {
	const static std::map<std::string, std::string> conv_tbl = {
		{"don't", "do not"}, {"can't", "cannot"}, {"won't", "will not"},
		{"couldn't", "could not"}, {"shouldn't", "should not"},
		{"wouldn't", "would not"}, {"aren't", "are not"}, {"weren't", "were not"},
		{"didn't", "did not"}, {"hasn't", "has not"}, {"haven't", "have not"},
		{"isn't", "is not"}, {"mustn't", "must not"}, {"shan't", "shall not"},
		{"wasn't", "was not"}
	};
	if (const auto it = conv_tbl.find(s); it != conv_tbl.cend())
		return it->second;
	return s;
}

std::string tolower(std::string s) {
	for (char& c : s) {
		c = std::tolower(c);
	}
	return s;
}

// Takes care of first character in a word:
//  - double quotes are removed
//  - quoted character is returned without formatting
//  - punctuation and space is removed
std::string handle_first_character(std::istream& is, bool& quoted) {
	std::ostringstream os;
	char ch = 0;
	if (is.get(ch)) {
		if (ch == '"')
			quoted = !quoted;
		else if (quoted)
			os << ch;
		else if (!is_mypunct(ch) && !isspace(ch))
			os << ch;
	}
	return os.str();
}

// Format a word read from given input stream:
// Quoted words:
//  - don't make any changes to the word
//  - remove quotes
// Normal words:
//  - remove punctuation
//  - don't remove '-' between words
//
// Classifies whether the returned string was in quotes
// or not, with the returned pair's second member
std::pair<std::string, bool> handle_word(std::istream& is, bool& quoted) {
	std::ostringstream os;
	os << handle_first_character(is, quoted);
	char ch = 0;
	// Read until space or double quote
	while (is.get(ch) && !std::isspace(ch) && ch != '"') {
		if (!quoted && is_mypunct(ch)) {
			if (ch == '-' && os.str().empty()) {
				continue;
			} else {
				char next = 0;
				if (is.get(next) && std::isalnum(next))
					is.unget();
				else {
					break;
				}
			}
		}
		os << ch;
	}
	// Let someone else handle trailing quote
	if (ch == '"') {
		is.unget();
	}
	return std::make_pair(os.str(), quoted);
}

// Modify strings using this rule:
//  - characters enclosed in double quotes '"' aren't modified
//  - punctuation characters are replaced to spaces if not in double quotes
//  - '-' allowed only between words
//  - characters are converted to lowercase
std::string modify(const std::string& s) {
	std::istringstream is{s};
	std::ostringstream os;
	// To keep track of formatting
	bool first_read = true;
	// Keep track of quoted words between calls
	static bool quoted = false;
	while (is) {
		// Get string and bool directly
		auto [word, is_quoted] = handle_word(is, quoted);
		// This indicates a quote-only or a space-only word,
		// don't print this
		if (word.empty() || (only_spaces(word) && !is_quoted)) {
			continue;
		}
		// Format only non-quoted words
		if (!is_quoted) {
			word = tolower(word);
			word = uncontract(word);
		}
		// Append space before writing another
		if (!first_read)
			os << ' ';
		os << word;
		first_read = false;
	}
	return os.str();
}

int main() {
	std::ifstream ist{"text.txt"};

	std::vector<std::string> words;
	for (std::string word; ist >> word; ) {
		words.push_back(modify(word));
	}
	std::ranges::sort(words);

	for (const std::string& word : words) {
		std::cout << word << '\n';
	}
}
