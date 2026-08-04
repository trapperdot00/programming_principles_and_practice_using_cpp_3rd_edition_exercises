#include <iostream>

int main()
{
	int i;
	int* p = &i;
	std::cout << p << '\n'; // Something like 0x7ffc9a5e4cf4
}
