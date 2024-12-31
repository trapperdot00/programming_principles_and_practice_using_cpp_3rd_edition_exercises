#include "../../../utils/PPPheaders.h"

int main()
try {
	int x = 2;
	double d = double(5)/x;
	if (d==x+0.5)
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
