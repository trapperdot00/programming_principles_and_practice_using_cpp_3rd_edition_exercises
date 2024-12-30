#include <string>
#include <iostream>

int main()
{
	std::string word;
	std::cin >> word;

	for (const char &c : word)
		std::cout << c << '\t' << int(c) << '\n';
}
