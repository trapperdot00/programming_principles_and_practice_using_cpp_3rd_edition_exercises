#include <iostream>

int main()
{
	int val1 = 0;
	int val2 = 0;
	while (std::cin >> val1 >> val2) {
		std::cout << val1 << '\t' << val2 << '\n';
	}
}
