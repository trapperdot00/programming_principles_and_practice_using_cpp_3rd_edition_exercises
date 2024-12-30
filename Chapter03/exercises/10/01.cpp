#include <iostream>

void calculate() {
	constexpr int square_count = 64;
	int square = 1;
	int grains = 1;
	while (square < square_count) {
		std::cout << square << '\t' << grains << '\n';
		grains *= 2;
		++square;
	}
}

int main()
{
	calculate();	// 31 max
}
