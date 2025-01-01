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

void print_calc(double a, double b, double c) {
	double d = discriminant(a, b, c);
	double x1 = (-b + std::sqrt(d)) / (2*a);
	double x2 = (-b - std::sqrt(d)) / (2*a);
	std::cout << "x1==" << x1 << "\nx2==" << x2 << '\n';
}

int main()
try {
	std::cout << "Enter a, b, c for the quadratic equation:\n";
	double a = 0.0;
	double b = 0.0;
	double c = 0.0;
	if (!(std::cin >> a >> b >> c))
		throw std::runtime_error("Invalid input!");
	print_calc(a, b, c);
} catch (std::exception& e) {
	std::cerr << "error: " << e.what() << '\n';
}
