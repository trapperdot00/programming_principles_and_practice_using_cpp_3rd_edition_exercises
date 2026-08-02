#include <iostream>

int main()
{
	constexpr int ia_size = 10;
	int* ia = new int[ia_size];

	std::cout << '{';
	for (int i = 0; i < ia_size; ++i)
	{
		if (i)
		{
			std::cout << ", ";
		}
		std::cout << ia[i];
	}
	std::cout << "}\n";
}
