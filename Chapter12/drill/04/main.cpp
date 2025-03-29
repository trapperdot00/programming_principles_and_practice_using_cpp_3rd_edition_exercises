#include "D1.h"

int main() {
	// Static and dynamic types match
	D1 d;

	d.vf();	// Calls D::vf
	d.f();	// Calls D::f

	// Static type: B1
	// Dynamic type: D1
	B1& bref = d;

	// Calls D::vf, virtual function
	bref.vf();
	// Calls B::f, not virtual
	bref.f();
}
