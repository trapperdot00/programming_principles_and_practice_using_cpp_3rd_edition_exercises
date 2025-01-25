#ifndef BOOK_H
#define BOOK_H

#include <chrono>
#include <string>
#include <cctype>
#include <stdexcept>
#include <iostream>

class Book {
public:
	Book(const std::string& is, const std::string& ti,
		 const std::string& au, int year, bool ch)
		: i(is), t(ti), a(au), cd(year), co(ch)
	{
		if (!valid_isbn(i))
			throw std::runtime_error{"Invalid ISBN format"};
	}
	Book(const std::string& is, const std::string& ti,
		 const std::string& au, int year)
		: Book(is, ti, au, year, false) {}

	std::string isbn() const { return i; }
	std::string title() const { return t; }
	std::string author() const { return a; }
	std::chrono::year copyright_date() const { return cd; }
	bool is_checked_out() const { return co; }

	void check_out() {
		if (is_checked_out())
			throw std::runtime_error{"book already checked out"};
		co = true;
	}
	void check_in() {
		if (!is_checked_out())
			throw std::runtime_error{"book already checked in"};
		co = false;
	}
private:
	bool valid_isbn(const std::string&) const;

	std::string i;	// ISBN No
	std::string t;	// Title
	std::string a;	// Author
	std::chrono::year cd;	// Copyright Date
	bool co;	// Book Checked Out
};

bool operator==(const Book&, const Book&);
bool operator!=(const Book&, const Book&);
std::ostream& operator<<(std::ostream&, const Book&);

#endif
