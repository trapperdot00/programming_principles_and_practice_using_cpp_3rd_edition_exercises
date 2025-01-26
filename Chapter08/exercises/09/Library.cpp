#include "Library.h"

bool Library::patron_exists(const Patron& sought) const noexcept {
	for (const Patron& patron : p) {
		if (patron.cardno() == sought.cardno())
			return true;
	}
	return false;
}
void Library::verify_patron(const Patron& patron) const {
	if (!patron_exists(patron))
		throw std::runtime_error{"patron doesn't exist with id "
			+ std::to_string(patron.cardno())};
}

auto Library::find_checked_in(const Book& book) -> std::vector<Book>::iterator {
	std::vector<Book>::iterator it = b.begin();
	while (it != b.end() && (it->title() != book.title() || it->is_checked_out()))
		++it;
	if (it == b.end())
		throw std::runtime_error{"checked in book (title: \""
			+ book.title()
			+ "\") not found"};
	return it;
}
auto Library::find_checked_in(const Book& book) const -> std::vector<Book>::const_iterator {
	std::vector<Book>::const_iterator it = b.cbegin();
	while (it != b.cend() && (it->title() != book.title() || it->is_checked_out()))
		++it;
	if (it == b.cend())
		throw std::runtime_error{"checked in book (title: \""
			+ book.title()
			+ "\") not found"};
	return it;
}

auto Library::find_checked_out(const Book& book) -> std::vector<Book>::iterator {
	std::vector<Book>::iterator it = b.begin();
	while (it != b.end() && (it->title() != book.title() || !it->is_checked_out()))
		++it;
	if (it == b.end())
		throw std::runtime_error{"checked out book (title: \""
			+ book.title()
			+ "\") not found"};
	return it;
}
auto Library::find_checked_out(const Book& book) const -> std::vector<Book>::const_iterator {
	std::vector<Book>::const_iterator it = b.cbegin();
	while (it != b.cend() && (it->title() != book.title() || !it->is_checked_out()))
		++it;
	if (it == b.cend())
		throw std::runtime_error{"checked out book (title: \""
			+ book.title()
			+ "\") not found"};
	return it;
}

void Library::verify_no_fees(const Patron& patron) const {
	if (owes(patron))
		throw std::runtime_error{"user (id: "
			+ std::to_string(patron.cardno())
			+ ") owes fees"};
}

void Library::check_out(const Patron& patron, const Book& book, const Date& date) {
	verify_patron(patron);
	const auto book_iter = find_checked_in(book);
	verify_no_fees(patron);
	book_iter->check_out();
	t.emplace_back(book, patron, date, Transaction::Action::check_out);
}

void Library::check_in(const Patron& patron, const Book& book, const Date& date) {
	verify_patron(patron);
	const auto book_iter = find_checked_out(book);
	book_iter->check_in();
	t.emplace_back(book, patron, date, Transaction::Action::check_in);
}

auto Library::owers() const -> std::vector<Patron> {
	std::vector<Patron> vec;
	for (const Patron& patron : p)
		if (owes(patron))
			vec.push_back(patron);
	return vec;
}
