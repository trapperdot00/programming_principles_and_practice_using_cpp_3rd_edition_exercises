#include <vector>
#include <iostream>
#include <utility>
#include <string>

void print(const std::vector<std::string>& vec) {
	for (const std::string& s : vec)
		std::cout << s << ' ';
	std::cout << '\n';
}

// Reverses a vector by copying the elements into another vector
// doesn't modify the passed vector
// uses reverse iterators to iterate over the elements backwards
auto reverse_copy(const std::vector<std::string>& vec) -> std::vector<std::string> {
	std::vector<std::string> ret;
	for (std::vector<std::string>::const_reverse_iterator it = vec.crbegin();
			it != vec.crend(); ++it) {
		ret.push_back(*it);
	}
	return ret;
}

// Reverses a vector of strings in-place
// swaps first with last element
// iterates towards the middle until reaching the center point
// doesn't swap the middle element if the number of elements is odd
void reverse(std::vector<std::string>& vec) {
	for (size_t i = 0; i < vec.size() / 2; ++i) {
		std::swap(vec[i], vec[vec.size()-i-1]);
	}
}

int main() {
	std::vector<std::string> vec1 = {"one", "two", "three", "four", "five"};
	print(vec1);

	std::vector<std::string> vec2 = reverse_copy(vec1);
	print(vec2);
	
	reverse(vec1);
	print(vec1);
}
