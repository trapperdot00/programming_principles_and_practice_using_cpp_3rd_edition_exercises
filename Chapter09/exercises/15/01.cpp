#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>

// Read numbers from a file with a given filename
auto read_file(const std::string& filename) -> std::vector<int> {
	std::ifstream ifs{filename};
	if (!ifs)
		throw std::runtime_error{"can't open " + filename + " for reading"};
	std::vector<int> numbers;
	for (int i = 0; ifs >> i; )
		numbers.push_back(i);
	return numbers;
}

// Counts the occurences of the integer elements of a sorted vector
auto count_occurences(const std::vector<int>& vec) -> std::vector<size_t> {
	// Return empty vector, to avoid returning a vector with an element of 0
	if (vec.empty())
		return {};
	std::vector<size_t> occurences;
	// We now know there is at least one element in the vector
	size_t count = 1;
	// Iterate from the second to the last element
	for (size_t i = 1; i < vec.size(); ++i) {
		if (vec[i - 1] != vec[i]) {
			occurences.push_back(count);
			count = 1;
		} else
			++count;
	}
	occurences.push_back(count);
	return occurences;
}

// Returns the index of the next different element in a vector,
// or the given index if the vector has no more subsciptable elements
auto next_different(const std::vector<int>& vec, size_t i) {
	size_t j = i + 1;
	if (j == vec.size())
		return i;
	while (j < vec.size() && vec[i] == vec[j])
		++j;
	return j;
}

// Print numbers and their occurences in separate lines,
// only print occurence if the number occured more than once
auto print_num_with_occurences
(std::ostream& os, std::vector<int> num)
-> std::ostream& {
	std::ranges::sort(num);
	std::vector<size_t> occ = count_occurences(num);
	size_t num_index = 0;
	for (size_t i = 0; i < occ.size(); ++i) {
		os << num[num_index];
		if (1 < occ[i])
			os << '\t' << occ[i];
		if (i + 1 != occ.size())
			os << '\n';
		num_index = next_different(num, num_index);
	}
	return os;
}

int main() {
	std::cout << "Enter input filename: ";
	std::string filename;
	if (!(std::cin >> filename))
		throw std::runtime_error{"no data"};

	std::vector<int> numbers = read_file(filename);
	print_num_with_occurences(std::cout, numbers) << '\n';
}
