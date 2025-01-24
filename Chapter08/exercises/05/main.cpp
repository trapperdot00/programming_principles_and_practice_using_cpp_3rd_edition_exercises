#include "Book.h"

#include <iostream>

using namespace std::chrono;

int main() {
	while (std::cin) try {
		std::string isbn;
		if (!(std::cin >> isbn))
			throw std::runtime_error{"no data"};
		year_month_day c_date{year{1970}, January, day{1}};
		std::string title{"Title"};
		std::string author{"Author"};
		bool check_out{false};
		
		Book b1{isbn, title, author, c_date, check_out};
		std::cout << "ISBN:\t\t" << b1.isbn() << '\n'
			<< "Title:\t\t" << b1.title() << '\n'
			<< "Author:\t\t" << b1.author() << '\n'
			<< "Copyright date:\t" << b1.copyright_date() << '\n'
			<< "Checked out:\t" << b1.is_checked_out() << '\n';
	} catch (const std::exception& e) {
		std::cerr << e.what() << '\n';
	}
}
