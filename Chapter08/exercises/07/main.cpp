#include "Book.h"

#include <iostream>

int main() {
	Book b1{"1-1-1-D", "Book1", "James Books", 2020, Book::Genre::fiction};

	// Out of bounds genre that int_to_genre converts to Book::Genre{0}
	// which can be printed as "not a genre"
	Book b2{"2-2-2-F", "Book2", "Chris Cooks", 2014, int_to_genre(11)};

	// Children genre
	Book b3{"3-3-3-3", "Book3", "Liz Looks", 2023, int_to_genre(5)};

	std::cout << "b1:\n" << b1 << '\n'
		<< "\nb2:\n" << b2 << '\n'
		<< "\nb3:\n" << b3 << '\n' << std::boolalpha
		<< "\nb1 == b2: " << (b1 == b2)
		<< "\nb1 != b2: " << (b1 != b2)
		<< "\nb1 == b3: " << (b1 == b3)
		<< "\nb1 != b3: " << (b1 != b3)
		<< "\nb2 == b3: " << (b2 == b3)
		<< "\nb2 != b3: " << (b2 != b3)
		<< '\n';
}
