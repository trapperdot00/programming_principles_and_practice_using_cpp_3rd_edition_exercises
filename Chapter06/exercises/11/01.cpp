/*	Rework of Chapter04/exercises/07
 *
 *	Simple quadratic equation solver that can only handle real solutions
 *
 */

#include <iostream>
#include <cmath>
#include <stdexcept>
#include <string>

template <typename T>
void expect(T f, const std::string &msg) {
	if (!f())
		throw std::runtime_error(msg);
}

double discriminant(double a, double b, double c) {
	double d = b*b - 4*a*c;
	expect([&]{ return d >= 0; }, "Negative discriminant: no real roots!");
	return d;
}

double get_x1(double discr, double a, double b) {
	return (-b + std::sqrt(discr)) / (2*a);
}

double get_x2(double discr, double a, double b) {
	return (-b - std::sqrt(discr)) / (2*a);
}

// Quadratic formula calculation loop
void calculate() {
	while (std::cin) try {
		std::cout << "Enter a, b, c for the quadratic equation:\n";
		double a = 0.0;
		double b = 0.0;
		double c = 0.0;
		if (!(std::cin >> a >> b >> c))
			throw std::runtime_error("Invalid input!");
		double discr = discriminant(a, b, c);
		std::cout << "x1==" << get_x1(discr, a, b)
			<< "\nx2==" << get_x2(discr, a, b) << '\n';
	} catch (std::exception& e) {
		std::cerr << "error: " << e.what() << '\n';
	}
}

int main()
try {
	calculate();
} catch (std::exception& e) {
	std::cerr << e.what() << '\n';
} catch (...) {
	std::cerr << "exception\n";
}
