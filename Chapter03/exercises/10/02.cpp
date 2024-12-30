#include <iostream>

void calculate() {
	int square = 1;
	double grains = 1;
	while (square < 2000) {
		std::cout << square << '\t' << grains << '\n';
		grains *= 2;
		++square;
	}
}

int main()
{
	calculate();	// 1024 max
}
