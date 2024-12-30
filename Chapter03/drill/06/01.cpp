#include <iostream>

int main()
{
	double smallest = 0.0;
	double largest = 0.0;
	double val = 0.0;

	// Initial reading
	if (std::cin >> val) {
		std::cout << val << '\n';
		smallest = val;
		largest = val;
	}

	while (std::cin >> val) {
		std::cout << val << '\n';
		if (val>largest) {
			largest = val;
			std::cout << "The largest so far.\n";
		} else if (val<smallest) {
			smallest = val;
			std::cout << "The smallest so far.\n";
		}
	}
}
