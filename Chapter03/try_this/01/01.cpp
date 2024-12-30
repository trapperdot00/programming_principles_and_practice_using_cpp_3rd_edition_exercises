#include <iostream>

int main()
{
	constexpr double dollar_per_yen = 0.0063;
	constexpr double dollar_per_kroner = 0.088;
	constexpr double dollar_per_pound = 1.26;

	double amount = 0;
	char currency = ' ';

	std::cin >> amount >> currency;

	if (currency == 'y')
		std::cout << amount << "y == " << amount * dollar_per_yen << "$\n";
	else if (currency == 'k')
		std::cout << amount << "k == " << amount * dollar_per_kroner << "$\n";
	else if (currency == 'p')
		std::cout << amount << "p == " << amount * dollar_per_pound << "$\n";
	else
		std::cout << "Invalid currency: " << currency << '\n';
}
