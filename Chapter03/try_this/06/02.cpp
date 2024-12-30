#include <iostream>
#include <vector>
#include <string>

int main()
{
	const std::vector<std::string> disliked = {
		"wanna", "gonna", "moist", "shoulda", "finna"
	};

	std::vector<std::string> words;
	for (std::string temp; std::cin >> temp; )
		words.push_back(temp);

	for (decltype(words)::size_type i = 0; i < words.size(); ++i) {
		decltype(disliked)::size_type j = 0;
		while (j < disliked.size() && disliked[j] != words[i])
			++j;
		if (j == disliked.size())
			std::cout << words[i] << '\n';
		else
			std::cout << "BLEEP\n";
	}
}
