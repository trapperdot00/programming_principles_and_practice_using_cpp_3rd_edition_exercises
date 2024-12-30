#include <iostream>
#include <string>
#include <vector>

int main()
{
	const std::string disliked = "moist";

	std::vector<std::string> words;
	for (std::string temp; std::cin >> temp; )
		words.push_back(temp);

	for (decltype(words)::size_type i = 0; i < words.size(); ++i) {
		if (words[i] != disliked)
			std::cout << words[i] << '\n';
		else
			std::cout << "BLEEP\n";
	}
}
