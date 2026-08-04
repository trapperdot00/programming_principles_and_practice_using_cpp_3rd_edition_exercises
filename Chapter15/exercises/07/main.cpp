#include <string>
#include <iostream>

int main()
{
	std::string s;

	std::cout << "Enter characters, exit using '!'\n";
	for (char c; std::cin.get(c) && c != '!'; s += c) ;

	std::cout << "Entered characters:\n";
	std::cout << s;
}
