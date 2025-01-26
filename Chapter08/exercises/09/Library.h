#ifndef LIBRARY_H
#define LIBRARY_H

#include "Book.h"
#include "Patron.h"
#include "Transaction.h"

#include <vector>
#include <stdexcept>

class Library {
public:
	void add_book(const Book& book) { b.push_back(book); }

	void add_patron(const Patron& patron) {
		if (patron_exists(patron))
			throw std::runtime_error{"patron already exists"};
		p.push_back(patron);
	}

	void check_out(const Patron&, const Book&, const Date&);
	void check_in(const Patron&, const Book&, const Date&);

	auto owers() const -> std::vector<Patron>;

	auto books() const -> std::vector<Book> { return b; }
	auto patrons() const -> std::vector<Patron> { return p; }
	auto transactions() const -> std::vector<Transaction> { return t; }

private:
	// Check if patron exists with the same id
	// in vector p
	bool patron_exists(const Patron&) const noexcept;
	// Call patron_exists and throw error if it returns false
	void verify_patron(const Patron&) const;
	// Find a checked in book with the same title as the given book
	// Returns an iterator that points to the book or throws an error
	auto find_checked_in(const Book&) -> std::vector<Book>::iterator;
	auto find_checked_in(const Book&) const ->	std::vector<Book>::const_iterator;
	// Find a checked out book with the same title as the given book
	// Returns an iterator that points to the book or throws an error
	auto find_checked_out(const Book&) -> std::vector<Book>::iterator;
	auto find_checked_out(const Book&) const -> std::vector<Book>::const_iterator;
	// Throw error if patron owes fees
	void verify_no_fees(const Patron&) const;

	std::vector<Book> b;		// Multiset of books
	std::vector<Patron> p;		// Set of patrons with unique card numbers
	std::vector<Transaction> t;	// List of transactions
};

#endif
