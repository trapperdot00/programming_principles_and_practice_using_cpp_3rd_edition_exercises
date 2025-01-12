#include <iostream>

namespace X {
	int var;
	void print() { std::cout << "X: " << var << '\n'; }
}
namespace Y {
	int var;
	void print() { std::cout << "Y: " << var << '\n'; }
}
namespace Z {
	int var;
	void print() { std::cout << "Z: " << var << '\n'; }
}

int main() {
	X::var = 7;
	X::print();
	using namespace Y;	// Now every member of Y is visible
	var = 9;	// Y::var
	print();	// Y::print
	{
		using Z::var;	// Z::var hides Y::var as var
		using Z::print;	// Z::print hides Y::print as print
		var = 11;	// Z::var
		print();	// Z::print
	}
	print();	// Y::print
	X::print();
}
