#include <iostream>
#include <string>

int main()
{
	std::cout << "Enter an operation followed by two operands:\n";
	
	std::string operation;
	double num1 = 0;
	double num2 = 0;
	std::cin >> operation >> num1 >> num2;

	if (operation == "+" || operation == "plus") {
		std::cout << num1 + num2 << '\n';
	} else if (operation == "-" || operation == "minus") {
		std::cout << num1 - num2 << '\n';
	} else if (operation == "*" || operation == "mul") {
		std::cout << num1 * num2 << '\n';
	} else if (operation == "/" || operation == "div") {
		std::cout << num1 / num2 << '\n';
	}
}
