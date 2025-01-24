#ifndef BOOK_H
#define BOOK_H

#include <chrono>
#include <string>
#include <cctype>

class Book {
public:
	Book(const std::string& is, const std::string& ti,
		 const std::string& au, const std::chrono::year_month_day& c, bool ch)
		: i(is), t(ti), a(au), cd(c), co(ch)
	{
		if (!valid_isbn(i))
			throw std::runtime_error{"Invalid ISBN format"};
	}

	std::string isbn() const { return i; }
	std::string title() const { return t; }
	std::string author() const { return a; }
	std::chrono::year_month_day copyright_date() const { return cd; }
	bool is_checked_out() const { return co; }

	void check_out() { co = true; }
	void check_in() { co = false; }
private:
	bool valid_isbn(const std::string&) const;

	std::string i;	// ISBN No
	std::string t;	// Title
	std::string a;	// Author
	std::chrono::year_month_day cd;	// Copyright Date
	bool co = false;	// Book Checked Out
};

#endif
