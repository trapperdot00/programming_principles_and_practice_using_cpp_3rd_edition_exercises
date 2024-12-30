#include <iostream>

int main()
{
	std::cout << "How many pennies do you have?\n";
	int pennies = 0;
	std::cin >> pennies;

	std::cout << "How many nickels do you have?\n";
	int nickels = 0;
	std::cin >> nickels;

	std::cout << "How many dimes do you have?\n";
	int dimes = 0;
	std::cin >> dimes;

	std::cout << "How many quarters do you have?\n";
	int quarters = 0;
	std::cin >> quarters;

	std::cout << "How many half dollars do you have?\n";
	int half_dollars = 0;
	std::cin >> half_dollars;

	std::cout << "How many dollars do you have?\n";
	int dollars = 0;
	std::cin >> dollars;

	std::cout << "You have " << pennies;
	if (pennies == 1)
		std::cout << " penny.\n";
	else
		std::cout << " pennies.\n";

	std::cout << "You have " << nickels;
	if (nickels == 1)
		std::cout << " nickel.\n";
	else
		std::cout << " nickels.\n";

	std::cout << "You have " << dimes;
	if (dimes == 1)
		std::cout << " dime.\n";
	else
		std::cout << " dimes.\n";

	std::cout << "You have " << quarters;
	if (quarters == 1)
		std::cout << " quarter.\n";
	else
		std::cout << " quarters.\n";

	std::cout << "You have " << half_dollars;
	if (half_dollars == 1)
		std::cout << " half dollar.\n";
	else
		std::cout << " half dollars.\n";

	std::cout << "You have " << dollars;
	if (dollars == 1)
		std::cout << " dollar.\n";
	else
		std::cout << " dollars.\n";

	double value = pennies + nickels * 5 + dimes * 10 + quarters * 25 + half_dollars * 50 + dollars * 100;
	value /= 100;

	std::cout << "The value of all of your coins is " << value << " dollars.\n";
}
