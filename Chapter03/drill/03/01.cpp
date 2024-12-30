#include <iostream>

int main()
{
	int val1 = 0;
	int val2 = 0;
	while (std::cin >> val1 >> val2) {
		if (val1<val2)
			std::cout << "The smaller value is: " << val1
				<< "\nThe larger value is: " << val2 << '\n';
		else if (val2<val1)
			std::cout << "The smaller value is: " << val2
				<< "\nThe larger value is: " << val1 << '\n';
		else
			std::cout << "The numbers are equal.\n";
	}
}
