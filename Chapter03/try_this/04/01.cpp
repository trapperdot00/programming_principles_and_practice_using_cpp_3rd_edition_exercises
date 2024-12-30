#include <iostream>

int main()
{
	for (char c = 'a'; c <= 'z'; ++c)
		std::cout << c << '\t' << int(c) << '\n';
}
