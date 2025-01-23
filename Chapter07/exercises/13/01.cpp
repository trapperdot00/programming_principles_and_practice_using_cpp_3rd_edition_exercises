#include <vector>
#include <iostream>
#include <stdexcept>
#include <string>
#include <string_view>
#include <utility>

std::vector<int> lengths(const std::vector<std::string>& vec) {
	std::vector<int> ret;
	for (const std::string& s : vec)
		ret.push_back(s.size());
	return ret;
}

std::string longest(const std::vector<std::string>& vec) {
	if (vec.empty())
		throw std::runtime_error{"empty vector"};
	std::string ret = vec[0];
	for (size_t i = 1; i < vec.size(); ++i)
		if (ret.size() < vec[i].size())
			ret = vec[i];
	return ret;
}

std::string shortest(const std::vector<std::string>& vec) {
	if (vec.empty())
		throw std::runtime_error{"empty vector"};
	std::string ret = vec[0];
	for (size_t i = 1; i < vec.size(); ++i)
		if (ret.size() > vec[i].size())
			ret = vec[i];
	return ret;
}

std::string lex_first(const std::vector<std::string>& vec) {
	if (vec.empty())
		throw std::runtime_error{"empty vector"};
	std::string ret = vec[0];
	for (size_t i = 1; i < vec.size(); ++i)
		if (ret > vec[i])
			ret = vec[i];
	return ret;
}

std::string lex_last(const std::vector<std::string>& vec) {
	if (vec.empty())
		throw std::runtime_error{"empty vector"};
	std::string ret = vec[0];
	for (size_t i = 1; i < vec.size(); ++i)
		if (ret < vec[i])
			ret = vec[i];
	return ret;
}

auto read_vec(std::string_view quit) -> std::vector<std::string> {
	std::vector<std::string> ret;
	for (std::string temp; std::cin >> temp && temp != quit; )
		ret.push_back(std::move(temp));
	if (ret.empty())
		throw std::runtime_error{"no input"};
	return ret;
}

int main() {
	constexpr std::string_view terminate = "EXIT";

	std::cout << "Enter words ('" << terminate << "' to end reading): ";
	std::vector<std::string> words = read_vec(terminate);

	std::vector<int> lens = lengths(words);

	std::cout << "Lenghts:\n";
	for (size_t i = 0; i < lens.size(); ++i) {
		std::cout << lens[i] << '\t' << words[i] << '\n';
	}

	std::cout << "Shortest string: " << shortest(words)
		<< "\nLongest string: " << longest(words)
		<< "\nLexicographically first: " << lex_first(words)
		<< "\nLexicographically last: " << lex_last(words)
		<< '\n';
}
