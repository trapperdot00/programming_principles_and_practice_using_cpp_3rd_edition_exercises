#include <vector>
#include <string>
#include <string_view>
#include <iostream>
#include <utility>
#include <stdexcept>

// Changed v to be passed by const-reference instead of value
// Changed quit to be passed by const-reference instead of value
// Changed s, the range-for loop variable to be a const-reference instead of a copy
void print_until(const std::vector<std::string>& v, const std::string& quit) {
	for (const std::string& s : v) {
		if (s == quit)
			return;
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
		throw std::runtime_error{"no input"};
	return ret;
}

int main() {
	constexpr std::string_view terminates = "EXIT";
	std::cout << "Enter words (end reading with '" << terminates << "'): ";
	std::vector<std::string> words = read_vec(terminates);

	std::cout << "Enter word to print until: ";
	std::string quit = read();

	print_until(words, quit);
}
