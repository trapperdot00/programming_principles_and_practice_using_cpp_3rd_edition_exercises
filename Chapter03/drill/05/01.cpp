#include <iostream>

int main()
{
	constexpr double diff = 0.01;

	double val1 = 0.0;
	double val2 = 0.0;
	while (std::cin >> val1 >> val2) {
		if (val1==val2)
			std::cout << "The numbers are equal.\n";
		else {
			if (val1<val2) {
				std::cout << "The smaller value is: " << val1
					<< "\nThe larger value is: " << val2 << '\n';
				if (val1+diff>val2)
					std::cout << "The numbers are almost equal.\n";
			} else {
				std::cout << "The smaller value is: " << val2
					<< "\nThe larger value is: " << val1 << '\n';
				if (val2+diff>val1)
					std::cout << "The numbers are almost equal.\n";
			}
		}
	}
}
