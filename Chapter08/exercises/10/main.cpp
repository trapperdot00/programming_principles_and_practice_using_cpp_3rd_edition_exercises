#include "Date.h"

#include <iostream>

int main() {
	int year = 0;
	while (std::cin >> year) {
		std::cout << (leapyear(year) ? "leapyear" : "not a leapyear") << '\n';
	}
}
