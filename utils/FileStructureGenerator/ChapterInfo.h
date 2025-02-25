#ifndef CHAPTERINFO_H
#define CHAPTERINFO_H

#include <string>
#include <vector>
#include <iostream>

struct ChapterInfo {
	size_t number;
	std::vector<std::string> folder;
};

ChapterInfo parse_chapterinfo(std::istream&);

#endif
