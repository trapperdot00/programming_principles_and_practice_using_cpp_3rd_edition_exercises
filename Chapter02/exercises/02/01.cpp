#include <iostream>

int main()
{
	std::cout << "Enter miles: ";
	double miles = 0;
	std::cin >> miles;
	double kilometers = miles * 1.609;
	std::cout << miles << " miles is " << kilometers << " kilometers\n";
	return 0;
}
