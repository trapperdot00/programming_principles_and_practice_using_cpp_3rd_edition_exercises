#ifndef SECTIONTITLESPARSER_H
#define SECTIONTITLESPARSER_H

#include <string>
#include <fstream>
#include <map>
#include <stdexcept>

enum class PathType {
	None, File, Folder
};

enum class ContentType {
	None, Folders, Files
};

struct SectionTitles {	
	struct Titles {
		std::string title;
		std::string exercise_title;

		PathType pathtype{PathType::None};
		std::string path;

		ContentType contenttype{ContentType::None};
		std::string extension;
	};

	std::map<std::string, Titles> title;
};

SectionTitles parse_sectiontitles(const std::string&);

#endif
