#ifndef POINT_H
#define POINT_H

#include <iostream>
#include <format>

struct Point {
	int x;
	int y;
};

bool operator==(const Point&, const Point&);
bool operator!=(const Point&, const Point&);

std::istream& operator>>(std::istream&, Point&);
std::ostream& operator<<(std::ostream&, const Point&);

// To allow usage of std::format with Point
// Delegates work to std::formatter<std::string>
// I don't yet fully understand how all of this works
template <>
struct std::formatter<Point> : std::formatter<std::string> {
	template <typename ParseContext>
	constexpr ParseContext::iterator parse(ParseContext& ctx) {
		return formatter<string>::parse(ctx);
	}
	template <typename FormatContext>
	FormatContext::iterator format(const Point& p, FormatContext& ctx) const {
		return formatter<string>::format(
			std::format("({},{})", p.x, p.y), ctx);
	}
};

#endif
