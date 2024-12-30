#include <iostream>

int main()
{
	char c = 'a';
	while (c <= 'z') {
		std::cout << c << '\t' << int(c) << '\n';
		++c;
	}
}
