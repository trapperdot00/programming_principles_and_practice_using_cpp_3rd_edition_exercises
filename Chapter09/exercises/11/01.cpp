#include <algorithm>
#include <mutex>
#include <string>
#include <fstream>
#include <iostream>
#include <stdexcept>

// Returns contents of file
std::string read_file(const std::string& filename) {
	std::ifstream ifs{filename};
	if (!ifs)
		throw std::runtime_error{"can't open " + filename + " for reading"};
	std::string contents;
	for (char ch = 0; ifs.get(ch); )
		contents += ch;
	return contents;
}

// Writes data to file after deleting its original contents
void write_file(const std::string& filename, const std::string& data) {
	std::ofstream ofs{filename};
	if (!ofs)
		throw std::runtime_error{"can't open " + filename + " for writing"};
	ofs << data;
}

// Reverses the contents of a file with a given filename
void reverse_file(const std::string& filename) {
	std::string file_contents = read_file(filename);
	std::ranges::reverse(file_contents);
	
	// Erase the newline character and add a newline to the end:
	// this might break binary file reversing!
	file_contents = file_contents.substr(1) + '\n';

	write_file(filename, file_contents);
}

int main() {
	std::cout << "Enter name of file to reverse: ";
	std::string filename;
	if (!(std::cin >> filename))
		throw std::runtime_error{"no data"};
	reverse_file(filename);
}
