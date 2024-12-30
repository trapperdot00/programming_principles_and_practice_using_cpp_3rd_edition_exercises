#include <iostream>
int main()
{
	std::cout << "Enter an integer: ";
	int number = 0;
	std::cin >> number;
	if (number % 2) {
		std::cout << "The value " << number << " is an odd number.\n";
	} else {
		std::cout << "The value " << number << " is an even number.\n";
	}
}
