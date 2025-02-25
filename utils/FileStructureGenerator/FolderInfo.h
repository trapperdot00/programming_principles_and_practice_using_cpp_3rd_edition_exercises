#ifndef FOLDERINFO_H
#define FOLDERINFO_H

#include "ChapterInfo.h"

#include <fstream>

struct FolderInfo {
	std::vector<ChapterInfo> chapters;
};

FolderInfo parse_folderinfo(std::istream&);
FolderInfo parse_folderinfo(const std::string&);

#endif
