#ifndef READMEGENERATOR_H
#define READMEGENERATOR_H

#include <string_view>
#include <sstream>
#include <filesystem>
#include <array>
#include <algorithm>
#include <cctype>

#include "BookDataParser.h"
#include "ChapterInfoParser.h"
#include "SectionTitlesParser.h"

class ReadmeGenerator {
public:
	ReadmeGenerator(const std::filesystem::path p)
		: root{find_root(p)}, utils{root / "utils" / "ReadmeGenerator" / "config"},
   		book{parse_bookdata(utils / bookdatafilename)}	{}

	// Generate README file for the root directory
	std::string generate_root() const;

	// Generate README file for a given chapter's directory
	// TODO
	std::string generate_chapter(size_t) const;

	std::filesystem::path root_path() const { return root; }
	std::filesystem::path utils_path() const { return utils; }
private:
	// Work our way out from the given directory until
	// we find a directory with a name that is a chapter
	std::filesystem::path find_root(std::filesystem::path) const;
	// Get the chapter's path, assuming that it is directly in root
	std::filesystem::path get_chapter_path(size_t) const;
	// Gets the exercise with the largest numerical value
	size_t get_last_exercise(const std::filesystem::path&) const;
	std::string pad_number(size_t) const;
	std::string generate_description() const;
	// Holds the project's root path
	std::filesystem::path root;
	// Holds the project's utilities directory path
	std::filesystem::path utils;

	// Hold data about the details of the book
	BookData book = parse_bookdata(utils / bookdatafilename);
	// Hold data about the chapters and exercise names and amounts
	ChapterInfo chapters = parse_chapterinfo(utils / chapterdatafilename);
	// Hold data about the string translations into titles or exercisetitles
	SectionTitles sectiontitles = parse_sectiontitles(utils / sectiontitlesfilename);

	// The structured file that contains the data for the book title,
	// parts, their numbers, and their titles,
	// and their chapters, their numbers, and their titles
	// Must be in the utils path
	constexpr static std::string_view bookdatafilename = "BookData.txt";
	constexpr static std::string_view chapterdatafilename = "ChapterInfo.txt";
	constexpr static std::string_view sectiontitlesfilename = "SectionTitles.txt";
	// TODO put this in a file, not directly in the source code
	constexpr static std::string_view title =
		"# My answers for the exercises in the book 'Programming: Principles and Practice using C++ (3rd edition)'\n";
	constexpr static size_t zero_pad_width = 2;
	constexpr static char fill_char = '0';
};

// Check if given path has "Chapter" in its name
bool is_chapter(const std::filesystem::path&);

// Call is_chapter for every directory in given path,
// return true on first match
bool has_chapter_dir(const std::filesystem::path&);

// Return the chapter's number from the given string
// "Chapter05" -> 5
size_t chapter_number(const std::string&);

size_t file_count_in_directory(const std::filesystem::path&);

// Convert arabic integer to roman
std::string to_roman(size_t);

std::string format_to_mdlink(std::string);

#endif
