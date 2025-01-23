#include <iostream>

class Date {
public:
	Date(int yy, int mm, int dd)
		: y(yy), m(mm), d(dd) {}

	int year() { return y; }
	int month() { return m; }
	int day() { return d; }
private:
	int y;
	int m;
	int d;
};

std::ostream& operator<<(std::ostream& os, Date d) {
	return os << d.year() << '/' << d.month() << '/' << d.day();
}

int main() {
	Date d1{2025,1,23};
	std::cout << d1 << '\n';

	Date d2{d1};
	std::cout << d2 << '\n';
}
