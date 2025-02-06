#include "ReadmeGenerator.h"
#include <filesystem>

namespace fs = std::filesystem;

int main() {
	ReadmeGenerator rmg{fs::current_path()};
	std::cout << rmg.generate_root();

/*
	std::cout << "\n----------------\n";
	const auto cont = parse("testdata.txt");
	std::cout << cont.title << "\n";
	for (const auto& e : cont.chapters) {
		std::cout << e.part.part << '\t' << e.part.title
			<< '\t' << e.chapter << '\t' << e.title << '\n';
	}
*/
}
