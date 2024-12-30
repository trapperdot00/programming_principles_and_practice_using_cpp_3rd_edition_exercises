#include <iostream>

int main()
{
	constexpr double dollar_per_yen = 0.0063;
	constexpr double dollar_per_kroner = 0.088;
	constexpr double dollar_per_pound = 1.26;
	constexpr double dollar_per_swiss_franc = 1.11;

	double amount = 0;
	char currency = ' ';
	std::cin >> amount >> currency;

	switch (currency) {
	case 'y':
		std::cout << amount << " yen == " << amount * dollar_per_yen << "$\n";
		break;
	case 'k':
		std::cout << amount << " kroner == " << amount * dollar_per_kroner << "$\n";
		break;
	case 'p':
		std::cout << amount << " pound == " << amount * dollar_per_pound << "$\n";
		break;
	case 's':
		std::cout << amount << " swiss franc == " << amount * dollar_per_swiss_franc << "$\n";
		break;
	default:
		std::cout << "Invalid currency: " << currency << '\n';
	}
}
