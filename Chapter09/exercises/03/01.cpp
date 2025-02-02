/* Didn't fully understand whether I needed to write the input file's contents
 * into a new file, or to change the given file in-place
 *
 * Settled on changing the file in-place, as it seemed new to me
 *
 * Tried to limit the scope/lifetime of file stream objects but I couldn't
 * separate the two (I/O) file stream objects into two functions, so I
 * had to use close() on the ifstream object
 */

#include <array>
#include <string>
#include <sstream>
#include <fstream>
#include <stdexcept>
#include <iostream>

bool is_vowel(char c) {
	constexpr static std::array<char, 5> vowels = {
		'a', 'e', 'i', 'o', 'u'
	};
	for (size_t i = 0; i < vowels.size(); ++i)
		if (c == vowels[i])
			return true;
	return false;
}

// Only put consonants into the given ostream from
// characters read from the istream
void disemvowel(std::istream& is, std::ostream& os) {
	for (char c; is.get(c); ) {
		if (!is_vowel(c))
			os << c;
	}
}

// Read consonants from file into a ostringstream,
// then open the file for writing to erase its contents,
// then write the consonants into it
void disemvowel_file(const std::string& filename) {
	// Open file for writing
	std::ifstream ifs{filename};
	if (!ifs)
		throw std::runtime_error{"can't open file: " + filename};

	// Used to hold consonants in memory
	std::ostringstream consonants;
	// Fill consonants
	disemvowel(ifs, consonants);
	
	// Warning: don't try to use ifs
	ifs.close();

	// Open the same file for writing, erase its contents
	// (ifstream and ofstream can't open the same file twice at the same time)
	std::ofstream ofs{filename};
	if (!ofs)
		throw std::runtime_error{"can't open file: " + filename + " for writing"};

	// Write consonants to empty file
	ofs << consonants.str();
}

int main() {
	std::cout << "Enter filename: ";
	std::string filename;
	std::cin >> filename;

	disemvowel_file(filename);
}
