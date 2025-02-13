#include "BookDataParser.h"

void Part::add_chapter(const Chapter& c) {
	throw_if_exists(c.number);
	chapters.push_back(c);
}

void Part::add_chapter(Chapter&& c) {
	throw_if_exists(c.number);
	chapters.push_back(std::move(c));
}

const Chapter& Part::get_chapter(size_t n) const {
	for (const Chapter& c : chapters)
		if (c.number == n)
			return c;
	throw std::runtime_error{"given chapter not found"};
}

bool Part::chapter_exists(size_t n) const {
	for (const Chapter& c : chapters)
		if (c.number == n)
			return true;
	return false;
}

void Part::throw_if_exists(size_t n) const {
	if (chapter_exists(n))
		throw std::runtime_error{"chapter " + std::to_string(n) + " already exists"};
}

void BookData::add_part(const Part& p) {
	throw_if_exists(p.number());
	parts.push_back(p);
}

void BookData::add_part(Part&& p) {
	throw_if_exists(p.number());
	parts.push_back(std::move(p));
}

const Part& BookData::get_part(size_t n) const {
	for (const Part& p : parts)
		if (p.number() == n)
			return p;
	throw std::runtime_error{"part " + std::to_string(n) + " not found"};
}

const Chapter& BookData::get_chapter(size_t n) const {
	for (const Part& p : parts)
		if (p.chapter_exists(n))
			return p.get_chapter(n);
	throw std::runtime_error{"chapter " + std::to_string(n) + " not found"};
}

bool BookData::part_exists(size_t n) const {
	for (const Part& p : parts)
		if (p.number() == n)
			return true;
	return false;
}

void BookData::throw_if_exists(size_t n) const {
	if (part_exists(n))
		throw std::runtime_error{"part " + std::to_string(n) + " already exists"};
}

std::string read_until(std::istream& is, char end, const std::string& msg) {
	std::ostringstream ret;
	for (char c = 0; is.get(c) && c != end; )
		ret << c;
	if (!is)
		throw std::runtime_error{msg};
	return ret.str();
}

BookData parse_bookdata(const std::string& filename, char start, char end) {
	std::ifstream ifs{filename};
	if (!ifs)
		throw std::runtime_error{"cannot open file: " + filename};

	// Read starting { Book "title here"
	// and consume them in the process
	read_specific(ifs, start, std::string{"expected "} + start + " to start book");
	read_specific<std::string>(ifs, "Book", "expected 'Book' label");
	read_specific(ifs, '"', "expected opening \" for book title");
	std::string book_title = read_until(ifs, '"', "expected closing \" for book title");

	BookData book{book_title};

	// Part parsing
	while (exact_read(ifs, start)) {
		// Read Part N "title here" and consume them in the process
		read_specific<std::string>(ifs, "Part", "expected 'Part' label");
		size_t part_number = read<size_t>(ifs, "expected a number after 'Part' label");
		read_specific(ifs, '"', "expected opening \" for part title");
		std::string part_title = read_until(ifs, '"', "expected closing \" for part title");

		Part part{part_number, part_title};

		// Chapter parsing, while it is possible to read {
		// consumes { in the condition
		while (exact_read(ifs, start)) {
			// Read Chapter N "title here" }
			// and consume them in the process
			read_specific<std::string>(ifs, "Chapter", "expected 'Chapter' label");
			size_t chapter_number = read<size_t>(ifs, "expected a number after 'Chapter' label");
			read_specific(ifs, '"', "expected opening \" for chapter title");
			std::string chapter_title = read_until(ifs, '"', "expected closing \" for chapter title");
			read_specific(ifs, end, std::string{"expected "} + end + " to end a chapter");

			Chapter chapter{chapter_number, chapter_title};

			// Insert the read chapter with all the necessary data
			part.add_chapter(std::move(chapter));
		}
		// Check for part-closing }
		// consumes } in the process
		read_specific(ifs, end, std::string{"expected "} + end + " to end a part");

		book.add_part(std::move(part));
	}
	// Check for book-closing }
	// consumes } in the process
	read_specific(ifs, end, std::string{"expected "} + end + " to end book");
	// Anything after book-closing } is ignored!
	return book;
}
