#include <vector>
#include <iostream>
#include <cmath>

std::vector<int> sieve_of_eratosthenes(int limit) {
	constexpr int enabled = 0;
	constexpr int disabled = 1;
	std::vector<int> helper(limit);
	for (int i = 2; i <= std::sqrt(limit); ++i) {
		if (helper[i] == enabled) {
			for (int j = std::pow(i, 2); j < limit; j += i) {
				helper[j] = disabled;
			}
		}
	}
	std::vector<int> primes;
	for (int i = 1; i < limit; ++i) {
		if (helper[i] == enabled)
			primes.push_back(i);
	}
	return primes;
}

int main()
{
	std::vector<int> primes = sieve_of_eratosthenes(100);

	for (int i : primes)
		std::cout << i << ' ';
	std::cout << '\n';
}
