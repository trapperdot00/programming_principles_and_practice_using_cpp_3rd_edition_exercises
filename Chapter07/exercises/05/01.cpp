#include <vector>
#include <iostream>
#include <utility>

void print(const std::vector<int>& vec) {
	for (int i : vec)
		std::cout << i << ' ';
	std::cout << '\n';
}

// Reverses a vector by copying the elements into another vector
// doesn't modify the passed vector
// uses reverse iterators to iterate over the elements backwards
std::vector<int> reverse_copy(const std::vector<int>& vec) {
	std::vector<int> ret;
	for (std::vector<int>::const_reverse_iterator it = vec.crbegin();
			it != vec.crend(); ++it) {
		ret.push_back(*it);
	}
	return ret;
}

// Reverses a vector of ints in-place
// swaps first with last element
// iterates towards the middle until reaching the center point
// doesn't swap the middle element if the number of elements is odd
void reverse(std::vector<int>& vec) {
	for (size_t i = 0; i < vec.size() / 2; ++i) {
		std::swap(vec[i], vec[vec.size()-i-1]);
	}
}

int main() {
	std::vector<int> vec1 = {1,3,5,7,9};
	print(vec1);

	std::vector<int> vec2 = reverse_copy(vec1);
	print(vec2);
	
	reverse(vec1);
	print(vec1);
}
