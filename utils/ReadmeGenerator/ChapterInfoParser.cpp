#include "ChapterInfoParser.h"

ChapterInfo parse_chapterinfo(const std::string& filename) {
	std::ifstream is{filename};
	if (!is)
		throw std::runtime_error{"can't open " + filename + " for reading"};
	ChapterInfo chapters;
	char ch1 = 0;
	while ((is >> ch1) && ch1 == '{') {	// Chapter read loop
		std::string chapter_label;
		if (!(is >> chapter_label) || chapter_label != "Chapter")
			throw std::runtime_error{ "'Chapter' label expected" };
		size_t chapter_num = 0;
		if (!(is >> chapter_num))
			throw std::runtime_error{ "Chapter number expected" };
		char ch2 = 0;
		std::vector<Section> sections;
		while ((is >> ch2) && ch2 == '{') {	// Section read loop
			std::string section_label;
			if (!(is >> section_label) || section_label != "Section")
				throw std::runtime_error{ "'Section' label expected" };
			char ch3 = 0;
			if (!(is >> ch3) || ch3 != '"')
				throw std::runtime_error{ "\" expected to start section name" };
			std::string section;
			for (char c = 0; is.get(c) && c != '"'; )
				section += c;
			if (!is)
				throw std::runtime_error{ "\" expected to close section name" };
			char ch4 = 0;
			if (!(is >> ch4) || ch4 != '{')
				throw std::runtime_error{ "{ expected to open section amount" };
			size_t section_amount = 0;
			if (!(is >> section_amount))
				throw std::runtime_error{ "section amount expected" };
			char ch5 = 0;
			if (!(is >> ch5) || ch5 != '}')
				throw std::runtime_error{ "} expected to close section amount" };
			char ch6 = 0;
			if (!(is >> ch6) || ch6 != '}')
				throw std::runtime_error{ "} expected to close Section" };

			if (section_amount)
				sections.push_back(Section{std::move(section), section_amount});
		}
		if (sections.empty())
			throw std::runtime_error{"Empty chapter (" + std::to_string(chapter_num) + ")"};
		if (!is || ch2 != '}')
			throw std::runtime_error{ "} expected to close Chapter" };

		chapters.chapter.push_back(Chapter_data{chapter_num, std::move(sections)});
	}
	if (is && ch1 != '}')
		throw std::runtime_error{"Invalid file format"};
	return chapters;
}

const Chapter_data& ChapterInfo::find_chapter(size_t chapter_num) const {
	for (size_t i = 0; i < chapter.size(); ++i)
		if (chapter[i].number == chapter_num)
			return chapter[i];
	throw std::runtime_error{"No data for chapter" + std::to_string(chapter_num)};
}
