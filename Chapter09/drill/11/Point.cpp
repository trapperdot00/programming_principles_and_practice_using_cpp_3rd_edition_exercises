#include "Point.h"

// Format: (n,n)
// n is an integer
// (same as the output but whitespace is ignored)
std::istream& operator>>(std::istream& is, Point& p) {
	char ch1 = 0;	// Opening parenthesis
	if (!(is >> ch1))
		return is;
	if (ch1 != '(') {
		is.unget();	// Put read character back
		is.clear(std::ios::failbit);
		return is;
	}

	int x = 0;		// X coordinate
	if (!(is >> x))
		return is;

	char ch2 = 0;	// Comma
	if (!(is >> ch2))
		return is;
	if (ch2 != ',') {
		is.clear(std::ios::failbit);
		return is;
	}

	int y = 0;		// Y coordinate
	if (!(is >> y))
		return is;

	char ch3 = 0;	// Closing parenthesis
	if (!(is >> ch3))
		return is;
	if (ch3 != ')') {
		is.clear(std::ios::failbit);
		return is;
	}

	// Change p only if all reading succeeded so that
	// we avoid only partially changing p
	p = Point{x, y};
	return is;
}

std::ostream& operator<<(std::ostream& os, const Point& p) {
	return os << '(' << p.x << ',' << p.y << ")";
}
