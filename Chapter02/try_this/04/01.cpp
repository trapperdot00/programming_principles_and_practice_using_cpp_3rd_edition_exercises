#include <iostream>
#include <string>

int main()
{
	std::string previous;
	std::string current;
	while (std::cin >> current) {
		if (previous == current)
			std::cout << "repeated word: " << current << '\n';
		previous = current;
	}
}
