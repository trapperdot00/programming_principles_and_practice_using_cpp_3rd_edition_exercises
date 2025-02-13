#include "ReadmeGenerator.h"

#include <filesystem>
#include <cstring>

namespace fs = std::filesystem;

struct usage_error{};

int main(int argc, char* argv[]) try {
	ReadmeGenerator rmg{fs::current_path()};

	if (argc == 2 && std::strcmp(argv[1], "-r") == 0)
		std::cout << rmg.generate_root() << '\n';
	else if (argc == 3 && std::strcmp(argv[1], "-c") == 0)
		std::cout << rmg.generate_chapter(std::stoi(argv[2])) << '\n';
	else
		throw usage_error{};
} catch (const usage_error& e) {
	std::cout << "Usage: " + std::string(argv[0]) + " ([-c] [n]) | [-r]\n"
		"\t[-c]\tGenerate Readme file for a given chapter specified by [n]\n"
		"\t[-r]\tGenerate Readme file for the root folder\n";
}
