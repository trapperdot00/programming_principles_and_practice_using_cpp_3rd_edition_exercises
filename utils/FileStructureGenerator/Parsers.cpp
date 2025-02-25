#include "ChapterInfo.h"

ChapterInfo parse_chapterinfo(std::istream& is) {
	char ch1 = 0;
	if (!(is >> ch1) || ch1 != '{')
		throw std::runtime_error{"'{' expected"};
	std::string chapter_label;
	if (!(is >> chapter_label) || chapter_label != "Chapter")
		throw std::runtime_error{"'Chapter' label expected"};
	size_t num = 0;
	if (!(is >> num))
		throw std::runtime_error{"chapter number expected"};
	char ch2 = 0;
	std::vector<std::string> folder_names;
	while (is >> ch2 && ch2 == '{') {
		std::string folder_label;
		if (!(is >> folder_label))
			throw std::runtime_error{"'Folder' label expected"};
		char ch3 = 0;
		if (!(is >> ch3) || ch3 != '"')
			throw std::runtime_error{"'\"' expected"};
		std::string folder_name;
		for (char c = 0; is.get(c) && c != '"'; )
			folder_name += c;
		if (!is)
			std::runtime_error{"'\"' expected"};
		char ch4 = 0;
		if (!(is >> ch4) || ch4 != '}')
			throw std::runtime_error{"} expected"};
		folder_names.push_back(std::move(folder_name));
	}
	if (!is || ch2 != '}')
		throw std::runtime_error{"} expected"};
	return ChapterInfo{num, folder_names};
}

#include "FolderInfo.h"

FolderInfo parse_folderinfo(std::istream& is) {
	std::vector<ChapterInfo> chapters;
	for (char ch = 0; (is >> ch) && ch == '{'; ) {
		is.putback(ch);
		ChapterInfo chapter = parse_chapterinfo(is);
		chapters.push_back(std::move(chapter));
	}
	return FolderInfo{chapters};
}

FolderInfo parse_folderinfo(const std::string& filename) {
	std::ifstream is{filename};
	if (!is)
		throw std::runtime_error{"can't open " + filename + " for reading"};
	return parse_folderinfo(is);
}
