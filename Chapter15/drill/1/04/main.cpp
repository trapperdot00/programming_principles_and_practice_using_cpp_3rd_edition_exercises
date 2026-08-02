#include <iostream>

std::ostream& print_array(std::ostream& os, int* a, int n)
{
	os << '{';
	for (int i = 0; i < n; ++i)
	{
		if (i)
		{
			os << ", ";
		}
		os << a[i];
	}
	return os << '}';
}

int main()
{
	constexpr int ia_size = 10;
	int* ia = new int[ia_size];
	print_array(std::cout, ia, ia_size) << '\n';
	delete[] ia;
}
