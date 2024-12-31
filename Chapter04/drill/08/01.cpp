#include "../../../utils/PPPheaders.h"

int main()
try {
	bool c = false;
	if (!c)
		cout << "Success!\n";
	else
		cout << "Fail!\n";
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
