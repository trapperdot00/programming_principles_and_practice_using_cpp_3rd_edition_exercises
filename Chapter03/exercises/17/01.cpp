#include <cmath>
#include <iostream>

constexpr int two_solutions = 1;
constexpr int one_solution = 2;
constexpr int complex_solution = 3;

double square(double x) {
	return x * x;
}

double discriminant(double a, double b, double c) {
	return square(b) - 4*a*c;
}

constexpr int solution_type(double discr) {
	return discr == 0 ? one_solution
		: discr > 0 ? two_solutions
		: complex_solution;
}

double equation_plus(double a, double b, double c) {
	return (-b+std::sqrt(discriminant(a, b, c)))/(2*a);
}

double equation_minus(double a, double b, double c) {
	return (-b-std::sqrt(discriminant(a, b, c)))/(2*a);
}

int main()
{
	std::cout << "Enter a, b, and c to solve a quadratic equation: ";
	double a = 0.0;
	double b = 0.0;
	double c = 0.0;
	std::cin >> a >> b >> c;
	double x1 = equation_plus(a, b, c);
	double x2 = equation_minus(a, b, c);
	std::cout << "x1==" << x1 << "\nx2==" << x2 << '\n';
	switch (solution_type(discriminant(a, b, c))) {
	case two_solutions:
		std::cout << "The equation has two solutions.\n";
		break;
	case one_solution:
		std::cout << "The equation has one solution.\n";
		break;
	case complex_solution:
		std::cout << "The equation has complex solutions.\n";
		break;
	}
}
