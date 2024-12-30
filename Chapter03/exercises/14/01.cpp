#include <vector>
#include <iostream>
#include <cmath>

bool is_prime(int num) {
	if (num < 2)
		return false;
	for (int divisor = 2; divisor <= std::sqrt(num); ++divisor)
		if (num % divisor == 0)
			return false;
	return true;
}

std::vector<int> first_n_primes(int n) {
	std::vector<int> primes;
	int num = 2;
	while (primes.size() < n) {
		if (is_prime(num))
			primes.push_back(num);
		++num;
	}
	return primes;
}

int main()
{
	std::vector<int> primes;

	std::cout << "Enter n: ";
	int n = 0;
	std::cin >> n;

	primes = first_n_primes(n);

	for (int i : primes)
		std::cout << i << ' ';
	std::cout << '\n';
}
