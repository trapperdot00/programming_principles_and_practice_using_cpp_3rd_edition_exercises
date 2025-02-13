#include "ReadmeGenerator.h"
#include <filesystem>
#include <iterator>
#include <string>

namespace fs = std::filesystem;

std::string ReadmeGenerator::generate_root() const {
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
	// Go through parts
	for (size_t i = 0; i < book.size(); ++i) {
		bool part_printed = false;
		const Part& part = book[i];
		// Go through chapters
		for (size_t j = 0; j < part.size(); ++j) {
			const Chapter& chapter = part[j];
			if (std::find(read_chapters.cbegin(),read_chapters.cend(),
					chapter.number) == read_chapters.cend())
				continue;
			if (!part_printed) {
				os << "\n## Part " << to_roman(part.number()) << ": " << part.title() << '\n';
				part_printed = true;
			}
			os << "### [Chapter" << std::setw(zero_pad_width)
				<< std::setfill('0') << chapter.number
				<< "](Chapter" << std::setw(zero_pad_width)
				<< std::setfill('0') << chapter.number
				<< "/): " << chapter.title
				<< '\n';
		}
	}
	return os.str();
}

// TODO
std::string ReadmeGenerator::generate_chapter(size_t chapter_num) const {
	fs::path chapter_path = get_chapter_path(chapter_num);

	const Chapter_data& exercise_data = chapters.find_chapter(chapter_num);

	std::ostringstream os;
	os << "# " << exercise_data.number << ": "
		<< book.get_chapter(chapter_num).title << "\n\n";
	for (const Section& sec : exercise_data.section) {
		const SectionTitles::Titles& titles = sectiontitles.title.at(sec.name);
		switch (titles.pathtype) {
		case PathType::Folder:
			os << "- ["
				<< titles.title
				<< "](#"
				<< format_to_mdlink(titles.exercise_title + " 1")
				<< ")\n";
			break;
		case PathType::File:
			os << "- ["
				<< titles.title
				<< "]("
				<< titles.path
				<< ")\n";
			break;
		default:
			throw std::runtime_error{"unhandled case for pathtype"};
		}
	}

	bool first_run = true;
	const Chapter_data chapter_data = chapters.find_chapter(chapter_num);
	for (const Section& sec : chapter_data.section) {
		const SectionTitles::Titles& titles = sectiontitles.title.at(sec.name);
		if (titles.pathtype == PathType::File)
			continue;
		if (first_run)
			first_run = false;
		else
			os << '\n';
		for (size_t num = 1; num <= sec.amount; ++num) {
			fs::path exercise_path{chapter_path / titles.path / (pad_number(num) +
				(titles.contenttype == ContentType::Files ? titles.extension : ""))};
			if (fs::exists(exercise_path)) {
				switch (titles.contenttype) {
				case ContentType::Folders:
				{
					std::string filename{(file_count_in_directory(exercise_path) == 1
							? '/' + fs::directory_iterator{exercise_path}->path().filename().string()
							: "")
					};
					os << "\n\n## ["
						<< titles.exercise_title
						<< ' '
						<< num
						<< "]("
						<< titles.path
						<< '/'
						<< pad_number(num)
						<< filename
						<< ")\n";
					break;
				}
				case ContentType::Files:
					os << "\n\n## ["
						<< titles.exercise_title
						<< ' '
						<< num
						<< "]("
						<< titles.path
						<< '/'
						<< pad_number(num)
						<< titles.extension
						<< ")\n";
					break;
				default:
					throw std::runtime_error{"unhandled case for contenttype"};
				}
			} else {
				os << "\n\n## "
					<< titles.exercise_title
					<< ' '
					<< num
					<< '\n';
			}
		}
	}
	return os.str();
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

fs::path ReadmeGenerator::get_chapter_path(size_t chapter_num) const {
	std::ostringstream dir_name;
	dir_name << "Chapter" << pad_number(chapter_num);
	fs::path chapter_path = root / dir_name.str();
	if (!fs::exists(chapter_path))
		throw std::runtime_error{chapter_path.string() + " doesn't exist"};
	return chapter_path;
}

size_t ReadmeGenerator::get_last_exercise(const fs::path& p) const {
	size_t ret = 0;
	bool first_run = true;
	for (const fs::directory_entry& e : fs::directory_iterator{p}) {
		size_t curr = std::stoi(e.path().filename());
		if (first_run || ret < curr) {
			ret = curr;
			first_run = false;
		}
	}
	return ret;
}

std::string ReadmeGenerator::pad_number(size_t n) const {
	std::ostringstream os;
	os << std::setw(zero_pad_width) << std::setfill(fill_char) << n;
	return os.str();
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
		if (e.is_directory() && is_chapter(e.path().filename())) {
			return true;
		}
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

size_t file_count_in_directory(const fs::path& p) {
	return std::distance(fs::directory_iterator{p}, fs::directory_iterator{});
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

std::string format_to_mdlink(std::string s) {
	for (char &c : s) {
		if (std::isalpha(c))
			c = std::tolower(c);
		else if (std::isspace(c))
			c = '-';
	}
	return s;
}
