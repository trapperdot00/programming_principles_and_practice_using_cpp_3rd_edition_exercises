#include <iostream>
#include <vector>

bool is_prime(int num) {
	if (num < 2)
		return false;
	int divisor_count = 0;
	for (int divisor = 1; divisor <= num / 2; ++divisor)
		if (num % divisor == 0)
			++divisor_count;
	return divisor_count == 1;
}

int main()
{
	const std::vector<int> primes = {
		2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53,59,61,67,71,73,79,83,89,97
	};
	constexpr int limit = 100;

	std::vector<int> found;
	for (int i = 1; i <= limit; ++i) {
		if (is_prime(i))
			found.push_back(i);
	}

	std::cout << "Prime numbers:\n";
	for (int i : primes)
		std::cout << i << ' ';

	std::cout << "\n\nMy solution:\n";
	for (int i : found)
		std::cout << i << ' ';
	std::cout << '\n';
}
