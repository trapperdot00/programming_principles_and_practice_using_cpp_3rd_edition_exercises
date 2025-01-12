struct X {
	void f(int x) {	// confusing parameter name
		struct Y {	// local class
			int f() { return 1; }
			int m;	// warning: undefined
		};
		int m;
		m = x;	// why couldn't you just initialize m with x?
		Y m2;
		return f(m2.f());	// error: void function returns a value of int
	}
	int m;	// don't use m multiple places as it leads to confusion
			// also, the default constructor of X doesn't even initialize it,
			// leaving it in an undefined state
	void g(int m) {	// uses local m
		// this function really doesn't do anything
		if (0<m)
			f(m+2);
		else {
			g(m+2.3);	// pointless recursion until m > 0
		}
	}
	X() { }
	int m3() {}	// does not return a value, but requires to return an int

	void main() {	// don't just name any function as main!
		// also pointless
		X a;
		a.f(2);
	}
};
