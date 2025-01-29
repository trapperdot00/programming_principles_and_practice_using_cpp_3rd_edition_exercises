#include "Money.h"

void read(Money& m) {
	if (!(std::cin >> m))
		throw std::runtime_error{"read failed"};
}

int main()
try {
	Money dollars{Currency::USD};
	Money euros{Currency::EUR};
	Money forints{Currency::HUF};
	Money kroners{Currency::DKK};
	Money swiss_francs{Currency::CHF};

	for (;;) {
		std::cout << "Enter dollars: ";
		read(dollars);
		std::cout << dollars << "\nin euros: " << euros + dollars
			<< "\nin forints: " << forints + dollars
			<< "\nin kroners: " << kroners + dollars
			<< "\nin swiss francs: " << swiss_francs + dollars << '\n';
	}
} catch (const std::exception& e) {
	std::cerr << e.what() << '\n';
}
