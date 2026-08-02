#include <iostream>

void sizes(char ch, int i, int* p, bool b, double d, float f)
{
	std::cout << "the size of char   is " << sizeof(char)   << ' ' << sizeof(ch) << '\n';
	std::cout << "the size of int    is " << sizeof(int)    << ' ' << sizeof(i) << '\n';
	std::cout << "the size of int*   is " << sizeof(int*)   << ' ' << sizeof(p) << '\n';
	std::cout << "the size of bool   is " << sizeof(bool)   << ' ' << sizeof(b) << '\n';
	std::cout << "the size of double is " << sizeof(double) << ' ' << sizeof(d) << '\n';
	std::cout << "the size of float  is " << sizeof(float)  << ' ' << sizeof(f) << '\n';
}

int main()
{
	char   c{};
	int    i{};
	int*   p{};
	bool   b{};
	double d{};
	float  f{};
	sizes(c, i, p, b, d, f);
}
