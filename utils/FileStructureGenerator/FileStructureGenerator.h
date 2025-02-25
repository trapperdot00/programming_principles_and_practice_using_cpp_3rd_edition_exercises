#ifndef FILESTRUCTUREGENERATOR_H
#define FILESTRUCTUREGENERATOR_H

#include "FolderInfo.h"

#include <algorithm>
#include <filesystem>
#include <sstream>
#include <iomanip>

// Find book's root-directory by leaving directories upwards
// from a given path
std::filesystem::path book_rootdir(std::filesystem::path);

class FSGenerator {
public:
	FSGenerator(const std::string& f) : info{parse_folderinfo(f)},
		rootpath{book_rootdir(std::filesystem::current_path())}
	{
		if (info.chapters.empty())
			throw std::runtime_error{"empty folderinfo"};
		std::cout << rootpath.string() << '\n';
	}

	void generate(size_t) const;
private:
	std::vector<ChapterInfo>::const_iterator get_chapter_info(size_t) const;

	FolderInfo info;
	std::filesystem::path rootpath;
};

#endif
