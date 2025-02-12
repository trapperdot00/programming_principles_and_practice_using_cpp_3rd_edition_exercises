#include <fstream>
#include <iostream>
#include <string>
#include <sstream>

int sum(std::istream& is) {
	// We don't indent to call this function recursively,
	// we can safely hide its name with this int
	int sum = 0;
	for (std::string word; is >> word; ) {
		std::istringstream stream{word};
		int num = 0;
		if (stream >> num)
			sum += num;
	}
	return sum;
}

int sum(const std::string& filename) {
	std::ifstream ifs{filename};
	if (!ifs)
		throw std::runtime_error{"can't open " + filename + " for reading"};
	return sum(ifs);
}

int main() {
	std::cout << "Enter input filename:\n";
	std::string filename;
	if (!(std::cin >> filename))
		throw std::runtime_error{"no data"};

	std::cout << "Sum of each whitespace-separated integer: "
		<< sum(filename)
		<< '\n';
}
