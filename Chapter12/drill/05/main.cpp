#include "D1.h"

int main() {
	// Error: abstract class
	D1 d;

	d.vf();
	d.f();

	B1& bref = d;

	bref.vf();
	bref.f();
}
