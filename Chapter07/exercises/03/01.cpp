#include <vector>
#include <string>
#include <iostream>

void print(const std::string& s, const std::vector<int>& vec) {
	std::cout << s;
	for (int i : vec)
		std::cout << ' ' << i;
	std::cout << '\n';
}

void fibonacci(int x, int y, std::vector<int>& v, size_t n) {
	for (size_t i = 0; i < n; ++i) {
		v.push_back(x);
		int temp = x;
		x = y;
		y = temp + y;
	}
}

int main() {
	constexpr int x = 1;
	constexpr int y = 2;
	std::vector<int> numbers;
	fibonacci(x, y, numbers, 10);
	std::string label = "Fibonacci numbers:";
	print(label, numbers);
}
