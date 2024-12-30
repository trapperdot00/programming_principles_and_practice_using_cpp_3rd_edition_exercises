#include <iostream>

void calculate(int target) {
	constexpr int square_count = 64;
	int square = 1;
	int grains = 1;
	while (square < square_count && grains <= target) {
		grains *= 2;
		++square;
	}
	std::cout << square << " squares are required for " << target << " grains\n";
}

int main()
{
	constexpr int target1 = 1000;
	constexpr int target2 = 1000000;
	constexpr int target3 = 1000000000;

	calculate(target1);
	calculate(target2);
	calculate(target3);
}
