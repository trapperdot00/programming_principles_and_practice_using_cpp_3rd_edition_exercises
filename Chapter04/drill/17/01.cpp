#include "../../../utils/PPPheaders.h"

int main()
try {
	int x = 2000;	// wouldn't fit in a char
	int c = x;		// char would narrow and lose information!
	if (c==2000)
		cout << "Success!\n";
	return 0;
}
catch (exception &e) {
	cerr << "error: " << e.what() << '\n';
	return 1;
}
catch (...) {
	cerr << "Oops: unknown exception!\n";
	return 2;
}
