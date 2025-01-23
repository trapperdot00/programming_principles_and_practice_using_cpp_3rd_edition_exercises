#include <vector>
#include <string>
#include <string_view>
#include <iostream>
#include <stdexcept>
#include <utility>

void print_until_ss(const std::vector<std::string>& v, const std::string& quit) {
	bool seen = false;
	for (const std::string& s : v) {
		if (s == quit) {
			if (seen)
				return;
			seen = true;
		}
		std::cout << s << '\n';
	}
}

auto read_vec(std::string_view quit) -> std::vector<std::string> {
	std::vector<std::string> ret;
	for (std::string temp; std::cin >> temp && temp != quit; )
		ret.push_back(std::move(temp));
	if (ret.empty())
		throw std::runtime_error{"no input"};
	return ret;
}

auto read() -> std::string {
	std::string ret;
	if (!(std::cin >> ret))
		throw std::runtime_error{"no data"};
	return ret;
}

int main() {
	constexpr std::string_view terminates = "EXIT";
	std::cout << "Enter words (end reading with '" << terminates << "'): ";
	std::vector<std::string> words = read_vec(terminates);

	std::cout << "Enter word to print until its second occurence: ";
	std::string quit = read();

	print_until_ss(words, quit);
}
