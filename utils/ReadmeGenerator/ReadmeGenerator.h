#ifndef READMEGENERATOR_H
#define READMEGENERATOR_H

#include <string>
#include <string_view>
#include <sstream>
#include <iostream>
#include <filesystem>
#include <vector>
#include <array>
#include <map>

#include "BookDataParser.h"

class ReadmeGenerator {
public:
	ReadmeGenerator(const std::filesystem::path p)
		: root{find_root(p)}, utils{root / "utils" / "ReadmeGenerator"} {}

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

	// Holds the project's root path
	std::filesystem::path root;
	// Holds the project's utilities directory path
	std::filesystem::path utils;

	// TODO put this in a file, not directly in the source code
	constexpr static std::string_view title =
		"# My answers for the exercises in the book 'Programming: Principles and Practice using C++ (3rd edition)'\n";
};

// Check if given path has "Chapter" in its name
bool is_chapter(const std::filesystem::path&);

// Call is_chapter for every directory in given path,
// return true on first match
bool has_chapter_dir(const std::filesystem::path&);

// Return the chapter's number from the given string
// "Chapter05" -> 5
size_t chapter_number(const std::string&);

// Convert arabic integer to roman
std::string to_roman(size_t);

#endif
