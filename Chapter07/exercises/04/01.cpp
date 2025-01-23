#include <vector>
#include <string>
#include <iostream>
#include <limits>
#include <stdexcept>

void print(const std::string& s, const std::vector<int>& vec) {
	std::cout << s;
	for (int i : vec)
		std::cout << ' ' << i;
	std::cout << '\n';
}

void fibonacci(int x, int y, std::vector<int>& v, size_t n) {
	bool reached_overflow = false;
	for (size_t i = 0; i < n; ++i) {
		v.push_back(x);
		if (reached_overflow)
			break;
		int temp = x;
		x = y;
		if (y > std::numeric_limits<int>::max() - temp)
			reached_overflow = true;
		y = temp + y;
	}
}

void print_last(const std::vector<int>& vec) {
	if (vec.empty())
		throw std::runtime_error{"Empty vector"};
	std::cout << vec[vec.size()-1] << '\n';
}

int main() {
	constexpr int x = 1;
	constexpr int y = 2;
	std::vector<int> numbers;
	fibonacci(x, y, numbers, 1000);
	print("Fibonacci sequence:", numbers);
	print_last(numbers);
}
