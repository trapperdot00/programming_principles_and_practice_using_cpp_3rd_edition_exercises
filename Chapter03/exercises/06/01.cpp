#include <iostream>

int main()
{
	double val1 = 0.0;
	double val2 = 0.0;
	char op = ' ';
	while (std::cin >> val1 >> val2 >> op) {
		switch (op) {
		case '+':
			std::cout << "The sum of " << val1 << " and " << val2
				<< " is " << val1+val2 << '\n';
			break;
		case '-':
			std::cout << "The difference of " << val1 << " and " << val2
				<< " is " << val1-val2 << '\n';
			break;
		case '*':
			std::cout << "The product of " << val1 << " and " << val2
				<< " is " << val1*val2 << '\n';
			break;
		case '/':
			std::cout << "The quotient of " << val1 << " and " << val2
				<< " is " << val1/val2 << '\n';
			break;
		default:
			std::cout << "Unknown operator: " << op << '\n';
		}
	}
}
