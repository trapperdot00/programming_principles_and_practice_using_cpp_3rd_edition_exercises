#include "Library.h"

#include <iostream>

void add_books(Library& lib, const std::vector<Book>& books) {
	for (const Book& book : books)
		lib.add_book(book);
}

void add_patrons(Library& lib, const std::vector<Patron>& patrons) {
	for (const Patron& patron : patrons)
		lib.add_patron(patron);
}

int main() {
	Library lib;
	Date today{Year{2024}, Month::jan, 25};
	

	std::vector<Book> books {
		{"1-1-1-1", "Book1", "Author1", 2020, Book::Genre::nonfiction},
		{"2-2-2-2", "Book2", "Author1", 2021, Book::Genre::biography},
		{"3-3-3-3", "Book3", "Author2", 2003, Book::Genre::fiction},
		{"3-3-3-3", "Book3", "Author2", 2003, Book::Genre::fiction, true},
		{"4-4-4-4", "Book4", "Author3", 2010, Book::Genre::children, true},
		{"4-4-4-4", "Book4", "Author3", 2010, Book::Genre::children}
	};
	add_books(lib, books);

	std::vector<Patron> patrons {
		{"John Doe"},
		{"Jane Doe", 12},
		{"George"}
	};
	add_patrons(lib, patrons);

	std::cout << "Books in library:";
	for (const Book& book : lib.books())
		std::cout << '\n' << book << '\n'
			<< (book.is_checked_out() ? "checked out" : "available")
			<< '\n';

	std::cout << "\nPatrons in library:";
	for (const Patron& patron : lib.patrons())
		std::cout << '\n' << patron << '\n';

	lib.check_out(lib.patrons()[0], lib.books()[0], today);
	lib.check_out(lib.patrons()[0], lib.books()[1], today);

	// This fails as user owes
	// lib.check_out(lib.patrons()[1], lib.books()[2], today);

	lib.check_out(lib.patrons()[2], lib.books()[2], today);

	// This fails as book is already checked out
	// lib.check_out(lib.patrons()[2], lib.books()[3], today);
	
	// Refers to an already checked out book, but there is another
	// book with that name that is available
	lib.check_out(lib.patrons()[2], lib.books()[4], today);

	// Check in all books
	for (const Transaction& t : lib.transactions())
		lib.check_in(t.patron, t.book, t.date);

	std::cout << "\nTransactions:";
	for (const Transaction& t : lib.transactions()) {
		std::cout << '\n' << t.book << '\n' << t.patron << '\n'
			<< (t.action == Transaction::Action::check_in ? "check in" : "check out") << '\n';
	}
}
