#include "ReadmeGenerator.h"

namespace fs = std::filesystem;

std::string ReadmeGenerator::generate_root() const {
	// TODO get book filename as an argument maybe from the command-line
	const BookData book{parse(utils / "testdata.txt")};

	// Hold found chapter directory numbers
	std::vector<size_t> read_chapters;

	// Scan root directory for directories with Chapter in their names
	for (const fs::directory_entry& e : fs::directory_iterator{root}) {
		std::string entry_path = e.path().filename();
		if (e.is_directory() && is_chapter(e.path().filename())) {
			// Put only the chapter-number into the container
			read_chapters.push_back(chapter_number(entry_path));
		}
	}

	// README construction part:

	std::ostringstream os;
	os << title;
	size_t prev_part = 0;

	// Go through previously found chapter numbers
	for (size_t i = 0; i < read_chapters.size(); ++i) {
		size_t c = read_chapters[i];
		
		// Find parsed chapter with the same chapter number
		const auto it = book.chapters.find(Chapter{{0, ""}, c, ""});

		// If there is no match
		if (it == book.chapters.cend())
			throw std::runtime_error{"no data for chapter " + std::to_string(c)};

		// Insert Part section into the README
		if (!i || prev_part != it->part.part) {
			os << "\n## Part " << to_roman(it->part.part) << ": " << it->part.title << '\n';
			prev_part = it->part.part;
		}
		// Insert Chapter section into the README
		os << "### [Chapter" << std::setw(2) << std::setfill('0') << it->chapter
			<< "](Chapter" << std::setw(2) << std::setfill('0') << it->chapter << "/): "
			<< it->title << '\n';		
	}
	return os.str();
}

std::string ReadmeGenerator::generate_chapter(size_t n) const {
	// TODO
	return "";
}

fs::path ReadmeGenerator::find_root(fs::path p) const {
	// Go through directories towards the system root directory
	// until the currently checked directory has a chapter-directory
	while (p != p.root_directory() && !has_chapter_dir(p)) {
		p = p.parent_path();
	}
	// We couldn't find any directories with "Chapter" in them
	if (!has_chapter_dir(p))
		throw std::runtime_error{"couldn't find book root directory"};
	return p;
}

bool is_chapter(const fs::path& p) {
	std::string path = p.string();
	// TODO Really stupid Chapter directory detection
	// could be triggered by unwanted entries
	return path.find("Chapter") != std::string::npos;
}

bool has_chapter_dir(const fs::path& p) {
	// Check each directory in path for a chapter-directory
	for (const fs::directory_entry& e : fs::directory_iterator{p}) {
		if (e.is_directory() && is_chapter(e.path()))
			return true;
	}
	return false;
}

size_t chapter_number(const std::string& s) {
	std::istringstream is{s};
	// Skip until digit
	for (char c; (is >> c) && !std::isdigit(c); )
		;
	// If there weren't any digits
	if (!is)
		throw std::runtime_error{"can't get chapter_number from: " + s};

	// Read the full number
	is.unget();
	size_t ret = 0;
	is >> ret;

	return ret;
}

std::string to_roman(size_t n) {
	struct Roman {
		int arabic;
		std::string value;
	};
	constexpr static std::array<Roman, 13> conv_tbl = {{
		{1, "I"}, {4, "IV"}, {5, "V"}, {9, "IX"},
		{10, "X"}, {40, "XL"}, {50, "L"}, {90, "XC"},
		{100, "C"}, {400, "CD"}, {500, "D"}, {900, "CM"},
		{1000, "M"}
	}};
	// Out of roman number representation range
	if (!n || n > 3999)
		throw std::runtime_error{std::to_string(n) + " can't be represented with roman numerals"};

	std::ostringstream os;
	auto it = conv_tbl.crbegin();
	while (n > 0) {
		int res = n / it->arabic;
		n = n % it->arabic;
		while (res--) {
			os << it->value;
		}
		++it;
	}
	return os.str();
}
