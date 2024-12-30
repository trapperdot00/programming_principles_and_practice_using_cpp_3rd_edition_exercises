#include <iostream>

int main()
{
	double d = 0;
	while (std::cin >> d) {
		int i = d;
		char c = i;
		std::cout << "d==" << d
				<< " i==" << i
				<< " c==" << (int)c
				<< " char(" << c << ")\n";
	}
}
