#include "Money.h"

int main() {
	do try {
		std::cout << "Enter an amount of dollars: ";
		double val{};
		if (!(std::cin >> val))
			throw 0;
		Money m1{val};
		std::cout << m1 << '\n';
	} catch (...) {
		// Print newline when entering EOF
		std::cout << '\n';
	} while (std::cin);
}
