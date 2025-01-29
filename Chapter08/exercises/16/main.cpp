#include "Money.h"

void read(Money& m) {
	if (!(std::cin >> m))
		throw std::runtime_error{"read failed"};
}

int main()
try {
	Money m;
	for (;;) {
		read(m);
		std::cout << m << '\n';
	}
} catch (const std::exception& e) {
	std::cerr << e.what() << '\n';
}
