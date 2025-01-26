#ifndef BOOK_H
#define BOOK_H

#include <chrono>
#include <string>
#include <cctype>
#include <stdexcept>
#include <iostream>
#include <array>
#include <string_view>

class Book {
public:
	enum class Genre {
		null, fiction, nonfiction, periodical, biography, children
	};

	Book(const std::string& is, const std::string& ti,
		 const std::string& au, int year, Genre genre, bool ch = false)
		: i(is), t(ti), a(au), cd(year), g(genre), co(ch)
	{
		if (!valid_isbn(i))
			throw std::runtime_error{"Invalid ISBN format"};
	}

	std::string isbn() const { return i; }
	std::string title() const { return t; }
	std::string author() const { return a; }
	std::chrono::year copyright_date() const { return cd; }
	Genre genre() const { return g; }
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
	Genre g;	// Genre of book
	bool co;	// Book Checked Out
};

// Int to Book::Genre with bounds checking
constexpr auto int_to_genre(int i) -> Book::Genre {
	// If i out of bounds return null enumerator
	if (i < 0 || 5 < i)
		return Book::Genre{0};
	return Book::Genre{i};
}

// Explicit conversion from Book::Genre to int
constexpr auto to_int(Book::Genre g) -> int {
	return static_cast<int>(g);
}

// Translate to human-readable format
auto genre_to_str(Book::Genre) -> std::string_view;

std::ostream& operator<<(std::ostream&, Book::Genre);

bool operator==(const Book&, const Book&);
bool operator!=(const Book&, const Book&);
std::ostream& operator<<(std::ostream&, const Book&);

#endif
