#include "../../../utils/PPPheaders.h"

int main()
try {
	vector<int> v(5);	// Missing template typename
	for (int i = 0; i<=v.size(); ++i)	// Warning: iterates v.size()+1 times!
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
