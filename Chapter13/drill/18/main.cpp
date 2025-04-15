#include "Person.h"

#include <iostream>

int main() {
	Person p;
	std::cout << "Enter person: ";
	if (std::cin >> p)
		std::cout << p << '\n';
}
