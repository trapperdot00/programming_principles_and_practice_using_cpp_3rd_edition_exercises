#include "BookDataParser.h"

bool operator==(const Chapter& lhs, const Chapter& rhs) {
	return lhs.chapter == rhs.chapter;
}

bool operator<(const Chapter& lhs, const Chapter& rhs) {
	return lhs.chapter < rhs.chapter;
}

std::string read_until(std::istream& is, char end, const std::string& msg) {
	std::ostringstream ret;
	for (char c = 0; is.get(c) && c != end; )
		ret << c;
	if (!is)
		throw std::runtime_error{msg};
	return ret.str();
}

BookData parse(const std::string& filename, char start, char end) {
	std::ifstream ifs{filename};
	if (!ifs)
		throw std::runtime_error{"cannot open file: " + filename};

	BookData ret;
	// Read starting { Book "title here"
	// and consume them in the process
	read_specific(ifs, start, std::string{"expected "} + start + " to start book");
	read_specific<std::string>(ifs, "Book", "expected 'Book' label");
	read_specific(ifs, '"', "expected opening \" for book title");
	ret.title = read_until(ifs, '"', "expected closing \" for book title");

	// Part parsing
	while (exact_read(ifs, start)) {
		// Read Part N "title here" and consume them in the process
		read_specific<std::string>(ifs, "Part", "expected 'Part' label");
		size_t part = read<size_t>(ifs, "expected a number after 'Part' label");
		read_specific(ifs, '"', "expected opening \" for part title");
		std::string part_title = read_until(ifs, '"', "expected closing \" for part title");

		// Chapter parsing, while it is possible to read {
		// consumes { in the condition
		while (exact_read(ifs, start)) {
			// Read Chapter N { "title here" } }
			// and consume them in the process
			read_specific<std::string>(ifs, "Chapter", "expected 'Chapter' label");
			size_t chapter = read<size_t>(ifs, "expected a number after 'Chapter' label");
			read_specific(ifs, start, std::string{"expected "} + start + " to start a title");
			read_specific(ifs, '"', "expected opening \" for chapter title");
			std::string title = read_until(ifs, '"', "expected closing \" for chapter title");
			read_specific(ifs, end, std::string{"expected "} + end + " to end a title");
			read_specific(ifs, end, std::string{"expected "} + end + " to end a chapter");

			// Insert the read chapter with all the necessary data
			ret.chapters.emplace(Part{part, part_title}, chapter, title);
		}
		// Check for part-closing }
		// consumes } in the process
		read_specific(ifs, end, std::string{"expected "} + end + " to end a part");
	}
	// Check for book-closing }
	// consumes } in the process
	read_specific(ifs, end, std::string{"expected "} + end + " to end book");
	// Anything after book-closing } is ignored!
	return ret;
}
