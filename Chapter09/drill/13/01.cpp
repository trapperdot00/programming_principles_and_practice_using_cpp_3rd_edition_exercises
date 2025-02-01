#include "Point.h"

#include <vector>
#include <utility>
#include <stdexcept>

int main() {
	constexpr size_t maxsize = 7;

	std::cout << std::format("Enter {} points: ", maxsize);
	std::vector<Point> original_points;
	for (Point p; original_points.size() < maxsize && std::cin >> p; ) {
		original_points.push_back(std::move(p));
	}

	if (original_points.empty())
		throw std::runtime_error{"No data"};
	// Print a label for each column and a line (sequence of '-'s)
	// I didn't want to calculate the maximum widths, so I went
	// with 20 for the representation field and 10 for x and y
	// line is 44 times '-' as we also have a column separator 4 times
	std::cout << std::format(
			"\nPoints:\n|{:^20}|{:^10}|{:^10}|\n{:-<44}\n",
			"Representation", "x", "y", ""
			);
	for (const Point& p : original_points) {
		std::cout << std::format("|{:^20}|{:^10}|{:^10}|\n", p, p.x, p.y);
	}
}
