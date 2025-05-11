#include <iostream>

// I think this is more readable
int iterative_fac(int n) {
	int j = 1;
	while (n > 1)
		j *= n--;
	return j;
}

// This is cooler though
int recursive_fac(int n) {
	return n > 1 ? n * recursive_fac(n-1) : 1;
}

int main() {
	for (int i = 0; i < 21; ++i) {
		std::cout << i
			<< "! == "
			<< recursive_fac(i)
			<< " (recursive) == "
			<< iterative_fac(i)
			<< " (iterative)\n";
	}
}
