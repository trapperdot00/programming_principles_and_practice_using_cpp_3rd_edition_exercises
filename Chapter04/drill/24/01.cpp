#include "../../../utils/PPPheaders.h"

int main()
try {
	int x = 4;
	double d = double(5)/(x-2);
	if (d==x/2+0.5)
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
