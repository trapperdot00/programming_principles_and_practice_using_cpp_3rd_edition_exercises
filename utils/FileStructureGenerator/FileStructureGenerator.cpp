#include "FileStructureGenerator.h"
#include <filesystem>

namespace fs = std::filesystem;

void FSGenerator::generate(size_t ch_num) const {
	std::vector<ChapterInfo>::const_iterator it = get_chapter_info(ch_num);
	std::ostringstream dir;
	dir << "Chapter" << std::setw(2) << std::setfill('0') << ch_num;
	if (!fs::exists(rootpath / dir.str()))
		fs::create_directory(rootpath / dir.str());
	for (const std::string& s : it->folder) {
		fs::create_directory(rootpath / dir.str() / s);
	}
}

std::vector<ChapterInfo>::const_iterator
FSGenerator::get_chapter_info(size_t ch_num) const {
	std::vector<ChapterInfo>::const_iterator it = std::find_if(
		info.chapters.cbegin(),
		info.chapters.cend(),
		[ch_num](const ChapterInfo& c){ return c.number == ch_num; }
	);
	if (it == info.chapters.cend())
		throw std::runtime_error{
			"chapter " + std::to_string(ch_num) + " has no data"
		};
	return it;
}

fs::path book_rootdir(fs::path p) {
	// Traverse upwards from the current directory
	// until we find a directory that has 'Chapter' in its name
	while (p != p.root_directory() && std::none_of(
		fs::directory_iterator{p},
		fs::directory_iterator{},
		[](const fs::directory_entry& e) {
			return e.is_directory() &&
			e.path().filename().string().find("Chapter") != std::string::npos;
	})) {
		p = p.parent_path();
	}
	if (p == p.root_directory())
		throw std::runtime_error{"couldn't find book root directory"};
	return p;
}
