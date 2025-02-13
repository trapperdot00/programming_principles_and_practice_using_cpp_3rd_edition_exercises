#ifndef CHAPTERINFOPARSER_H
#define CHAPTERINFOPARSER_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <stdexcept>
#include <utility>

struct Section {
	std::string name;
	size_t amount;
};

struct Chapter_data {
	size_t number;
	std::vector<Section> section;
};

struct ChapterInfo {
	std::vector<Chapter_data> chapter;

	const Chapter_data& find_chapter(size_t) const;
};


ChapterInfo parse_chapterinfo(const std::string&);

#endif
