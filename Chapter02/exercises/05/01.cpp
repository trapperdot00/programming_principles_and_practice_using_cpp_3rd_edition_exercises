#include <iostream>

int main()
{
	std::cout << "Enter two floating-point values: ";
	double val1 = 0, val2 = 0;
	std::cin >> val1 >> val2;
	
	if (val1 < val2)
		std::cout << "The smaller one: " << val1
				<< "\nThe larger one: " << val2;
	else if (val2 < val1)
		std::cout << "The smaller one: " << val2
				<< "\nThe larger one: " << val1;
	else
		std::cout << "The numbers are equal";

	std::cout << "\nSum: " << val1 + val2
			<< "\nDifference: " << val1 - val2
			<< "\nProduct: " << val1 * val2
			<< "\nRatio: " << val1 / val2
			<< '\n';
}
