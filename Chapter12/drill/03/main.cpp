#include "D1.h"

int main() {
	D1 d;

	d.vf();
	d.f();

	B1& bref = d;
	bref.vf();
	bref.f();
}
