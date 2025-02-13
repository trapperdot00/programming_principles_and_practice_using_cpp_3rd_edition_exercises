#ifndef BOOKDATAPARSER_H
#define BOOKDATAPARSER_H

#include <fstream>
#include <sstream>
#include <string>
#include <utility>
#include <vector>
#include <stdexcept>
#include <iostream>

// Represents the number of a chapter of a book,
// the part that it is part of, and its title
struct Chapter {
	size_t number;
	std::string title;
};

class Part {
public:
	Part(size_t n, const std::string& s)
		: part_number(n), part_title(s) {}

	void add_chapter(const Chapter&);
	void add_chapter(Chapter&&);

	size_t number() const { return part_number; }
	std::string title() const { return part_title; }

	const Chapter& get_chapter(size_t) const;

	size_t size() const { return chapters.size(); }
	const Chapter& operator[](size_t n) const { return chapters.at(n); }
	bool chapter_exists(size_t) const;
private:
	void throw_if_exists(size_t) const;

	size_t part_number;
	std::string part_title;
	std::vector<Chapter> chapters;
};

// Represents the title of a book
// and all of its chapters sorted by the chapters' numbers ascending
class BookData {
public:
	BookData(const std::string& s)
		: book_title(s) {}

	void add_part(const Part&);
	void add_part(Part&&);

	const Part& get_part(size_t) const;
	const Chapter& get_chapter(size_t) const;

	std::string title() const { return book_title; }
	size_t size() const { return parts.size(); }
	const Part& operator[](size_t n) const { return parts.at(n); }

private:
	bool part_exists(size_t) const;
	void throw_if_exists(size_t) const;

	std::string book_title;
	std::vector<Part> parts;
};

bool operator==(const Chapter&, size_t);
bool operator<(const Chapter&, const Chapter&);

// Reads an object from a given input stream,
// If the reading fails or we don't get the item we wanted,
// throws an error with the given message
// Returns the object read
template <typename T>
T read_specific(std::istream& is, const T& want, const std::string& msg) {
	T t;
	if (!(is >> t) || t != want)
		throw std::runtime_error{msg};
	return t;
}

// Read an object of a given type,
// If the reading didn't succeed, throw an error with the given message
// Returns the read object
template <typename T>
T read(std::istream& is, const std::string& msg) {
	T t;
	if (!(is >> t))
		throw std::runtime_error{msg};
	return t;
}

// Read an object from the given input stream,
// consume and return true if we read the given value,
// else return false and put the value back into the stream
template <typename T>
bool exact_read(std::istream& is, const T& want) {
	T t;
	if (!(is >> t))
		return false;
	if (t == want)
		return true;
	is.unget();
	return false;
}

// Read characters until stream fails or end character is read
// Throws an error if stream is invalidated with the message given
// Returns the given sequence of characters
std::string read_until(std::istream&, char, const std::string&);

// Parse file format for holding data of books:
// example format:
//	{ Book "book title"
// 		{ Part 1 "part1 title"
//			{ Chapter 1 "chapter1 title" }
//			{ Chapter 2 "chapter2 title" }
//		}
//		{ Part 2 "part2 title"
//			{ Chapter 3 "chapter3 title" }
//		}
//	}
// Takes optional section starting and ending characters that default to curlies
// Returns a BookData with each of the values processed and inserted
BookData parse_bookdata(const std::string& filename, char s = '{', char e = '}');

#endif
