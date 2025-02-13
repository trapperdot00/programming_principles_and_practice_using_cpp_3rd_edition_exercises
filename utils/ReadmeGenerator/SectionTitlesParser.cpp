#include "SectionTitlesParser.h"

SectionTitles parse_sectiontitles(const std::string& filename) {
	std::ifstream is{filename};
	if (!is)
		throw std::runtime_error{"can't open " + filename + " for reading"};
	SectionTitles section_titles;
	char ch1 = 0;
	while ((is >> ch1) && ch1 == '{') {	// Section loop
		char ch2 = 0;
		if (!(is >> ch2) || ch2 != '"')
			throw std::runtime_error{"\" expected to start section title"};
		std::string section;
		for (char c = 0; is.get(c) && c != '"'; )
			section += c;
		if (!is)
			throw std::runtime_error{"expected closing \""};
		SectionTitles::Titles titles;
		char ch3 = 0;
		while ((is >> ch3) && ch3 == '{') {	// Keyword loop
			std::string keyword;
			if (!(is >> keyword))
				throw std::runtime_error{"keyword expected"};
			char ch4 = 0;
			if (!(is >> ch4) || ch4 != '"')
				throw std::runtime_error{"\" expected to start " + keyword + " value"};
			std::string value;
			for (char c = 0; is.get(c) && c != '"'; )
				value += c;
			if (!is)
				throw std::runtime_error{"expected closing \""};
			char ch5 = 0;
			if (!(is >> ch5) || ch5 != '}')
				throw std::runtime_error{"} expected to close " + keyword};
			if (keyword == "Title")
				titles.title = value;
			else if (keyword == "ExerciseTitle")
				titles.exercise_title = value;
			else if (keyword == "FolderName") {
				if (titles.pathtype != PathType::None)
					throw std::runtime_error{"only one pathtype allowed"};
				titles.pathtype = PathType::Folder;
				titles.path = value;
			} else if (keyword == "FileName") {
				if (titles.pathtype != PathType::None)
					throw std::runtime_error{"only one pathtype allowed"};
				titles.pathtype = PathType::File;
				titles.path = value;
			} else if (keyword == "FolderContents") {
				if (titles.contenttype != ContentType::None)
					throw std::runtime_error{"only one contenttype allowed"};
				if (value == "Folders")
					titles.contenttype = ContentType::Folders;
				else if (value == "Files")
					titles.contenttype = ContentType::Files;
				else
					throw std::runtime_error{"content types: Folders, Files"};
			} else if (keyword == "FileExtensions") {
				if (titles.contenttype != ContentType::Files)
					throw std::runtime_error{"to add an extension to a section, it needs to hold files"};
				titles.extension = value;
			}
		}
		if (!is || ch3 != '}')
			throw std::runtime_error{"} expected to close Section"};
		if (titles.title.empty() || titles.exercise_title.empty())
			if (titles.pathtype != PathType::File)
				throw std::runtime_error{
					"required keywords: Title; ExerciseTitle; FolderName; FolderContents"
				};
		
		section_titles.title[section] = std::move(titles);
	}
	return section_titles;
}
