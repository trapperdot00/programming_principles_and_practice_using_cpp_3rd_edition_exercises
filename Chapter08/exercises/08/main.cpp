#include "Patron.h"

#include <iostream>

int main() {
	Patron user1{"John Doe"};
	Patron user2{"Jane Doe", 320};
	std::cout << user1 << "\nowes: " << std::boolalpha << owes(user1)
		<< "\n\n" << user2 << "\nowes: " << owes(user2) << '\n';
	
	user1.set_name("Dr. John Doe");
	std::cout << '\n' << user1 << '\n';

	std::cout << "\nCard number increment test:\n";
	for (int i = 0; i < 20; ++i) {
		Patron user;
		std::cout << user.cardno() << '\n';
	}

	std::cout << "\nFee set and get test:\n";
	user1.set_fee(5);
	while (owes(user1)) {
		std::cout << user1 << "\nowes: " << owes(user1) << "\n\n";
		user1.set_fee(user1.fees()-1);
	}
	std::cout << user1 << "\nowes: " << owes(user1) << '\n';;

	Patron user3{"Sample"};
	std::cout << '\n' << user3 << '\n';
}
