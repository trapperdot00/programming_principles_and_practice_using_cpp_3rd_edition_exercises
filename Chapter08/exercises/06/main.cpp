#include "Book.h"

#include <iostream>

int main() {
	Book b1{"0-13-830868-3", "Programming: Principles and Practice Using C++ (3rd Edition)", "Bjarne Stroustrup", 2024};
	Book b2{"0-321-71411-3", "C++ Primer (5th Edition)", "Stanley B. Lippman, Josée Lajoie, Barbara E. Moo", 2013};
	Book b3{b1};
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
