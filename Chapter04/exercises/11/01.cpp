#include <iostream>
#include <stdexcept>
#include <limits>

int main()
try {
	std::cout << "Enter N: ";
	int n = 0;
	if (!(std::cin >> n))
		throw std::runtime_error("No data!");

	if (n <= 0)
		throw std::runtime_error("N can't be 0 or less!");

	std::cout << "The first " << n << " values in the Fibonacci series:\n";
	int a = 1;
	int b = 1;
	for (int i = 0; i < n; ++i) {
		if (i < 2)
			std::cout << a << ' ';
		else {
			// sign of overflow if this doesn't hold
			if (b > std::numeric_limits<int>::max() - a)
				throw std::runtime_error("overflow!");

			int temp = a + b;
			std::cout << temp << ' ';
			a = b;
			b = temp;
		}
	}
	std::cout << '\n';
} catch (std::exception& e) {
	std::cerr << "\nerror: " << e.what() << '\n';
}
