#include "D21.h"
#include "D22.h"

int main() {
	D21 d21;
	d21.value = "D21";

	D22 d22;
	d22.value = 22;

	f(d21);
	f(d22);
}
