#include <string>
#include <iostream>

int main()
{
	std::cout << "Enter a spelled-out number: ";
	std::string spelled_out_number;
	std::cin >> spelled_out_number;
	if (spelled_out_number == "zero")
		std::cout << 0 << '\n';
	else if (spelled_out_number == "one")
		std::cout << 1 << '\n';
	else if (spelled_out_number == "two")
		std::cout << 2 << '\n';
	else if (spelled_out_number == "three")
		std::cout << 3 << '\n';
	else if (spelled_out_number == "four")
		std::cout << 4 << '\n';
	else
		std::cout << "not a number I know\n";
}
