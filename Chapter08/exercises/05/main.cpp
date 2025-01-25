#include "Book.h"

#include <iostream>

int main() {
	while (std::cin) try {
		std::string isbn;
		if (!(std::cin >> isbn))
			throw std::runtime_error{"no data"};
		std::string title{"Title"};
		std::string author{"Author"};
		int year = 1970;
		bool check_out{false};
		
		Book b1{isbn, title, author, year, check_out};
		std::cout << "ISBN:\t\t" << b1.isbn() << '\n'
			<< "Title:\t\t" << b1.title() << '\n'
			<< "Author:\t\t" << b1.author() << '\n'
			<< "Copyright date:\t" << b1.copyright_date() << '\n'
			<< "Checked out:\t" << b1.is_checked_out() << '\n';
	} catch (const std::exception& e) {
		std::cerr << e.what() << '\n';
	}
}
