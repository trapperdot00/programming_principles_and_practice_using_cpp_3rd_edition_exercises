#include "FileStructureGenerator.h"
#include <filesystem>

namespace fs = std::filesystem;

int main(int argc, char* argv[]) {
	if (argc < 2)
		throw std::runtime_error{std::string("usage: ") + argv[0] + " [n]"};
	const std::string filename{
		book_rootdir(fs::current_path()) / "utils" / "FileStructureGenerator" / "config" / "FolderInfo.txt"
	};
	FSGenerator gen{filename};
	gen.generate(std::stoull(argv[1]));
}
