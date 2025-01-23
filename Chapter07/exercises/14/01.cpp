#include <iostream>
#include <stdexcept>
#include <string>

// It could come in handy when we don't want
// to accidentally change the value of a variable
// For example, the size is constant here, printing
// doesn't and shouldn't change it, or it might break the program
void print(const char *p, const size_t size) {
	if (!p)
		throw std::runtime_error{"nullptr"};
	for (size_t i = 0; i < size; ++i)
		std::cout << p[i];
	std::cout << '\n';
}

int main() {
	std::string s = "Hello, World!";
	print(s.c_str(), s.size());
}
