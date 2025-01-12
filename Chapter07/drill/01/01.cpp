#include <iostream>

// Will only swap the local variables!
void swap_v(int a, int b) {
	int temp;
	temp = a;
	a = b;
	b = temp;
}

// Does the actual swapping through references!
void swap_r(int& a, int& b) {
	int temp;
	temp = a;
	a = b;
	b = temp;
}

/*	Cannot assign to const reference!
 *	Garbage function!
void swap_cr(const int& a, const int& b) {
	int temp;
	temp = a;
	a = b;
	b = temp;
}*/

int main() {
	int x = 7;
	int y = 9;
	std::cout << "x==" << x << "\ty==" << y << '\n';
	swap_v(x, y);	// Swaps only the parameters local to swap_v
	std::cout << "x==" << x << "\ty==" << y << '\n';
	swap_r(x, y);	// The only working swap!
	std::cout << "x==" << x << "\ty==" << y << '\n';
//	swap_cr(x, y);
	swap_v(7, 9);	// Swaps only the parameters local to swap_v
	std::cout << "x==" << x << "\ty==" << y << '\n';
//	swap_r(7, 9);	error: rvalue passed to lvalue reference parameter
//	swap_cr(7, 9);

	const int cx = 7;
	const int cy = 9;
	std::cout << "cx==" << cx << "\tcy==" << cy << '\n';
	swap_v(cx, cy);	// Swaps only the parameters local to swap_v
	std::cout << "cx==" << cx << "\tcy==" << cy << '\n';
//	swap_r(cx, cy);	error: const object passed to non-const reference parameter
//	swap_cr(cx, cy);
	swap_v(7.7, 9.9);	// warning: narrowing conversion from double to int
	std::cout << "cx==" << cx << "\tcy==" << cy << '\n';
//	swap_r(7.7, 9.9);	error: cannot bind lvalue reference to rvalue
//	swap_cr(7.7, 9.9);

	double dx = 7.7;
	double dy = 9.9;
	std::cout << "dx==" << dx << "\tdy==" << dy << '\n';
	swap_v(dx, dy);	// Swaps only the parameters local to swap_v
	std::cout << "dx==" << dx << "\tdy==" << dy << '\n';
//	swap_r(dx, dy);	error: cannot bind int& to double
//	swap_cr(dx, dy);
	swap_v(7.7, 9.9);	// Swaps only the parameters local to swap_v
	std::cout << "dx==" << dx << "\tdy==" << dy << '\n';
//	swap_r(7.7, 9.9);	error: cannot bind lvalue reference to rvalue
//	swap_cr(7.7, 9.9);
}
