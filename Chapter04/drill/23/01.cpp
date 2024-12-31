#include "../../../utils/PPPheaders.h"

int main()
try {
	int i = 0;
	int j = 0;
	while (i<10)
		++i;
	if (j<i)
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
