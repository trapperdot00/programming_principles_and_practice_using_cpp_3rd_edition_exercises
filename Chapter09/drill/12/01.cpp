#include "Point.h"

#include <format>
#include <vector>
#include <utility>

int main() {
	constexpr size_t maxsize = 7;

	std::cout << std::format("Enter {} points: ", maxsize);
	std::vector<Point> original_points;
	for (Point p; original_points.size() < maxsize && std::cin >> p; ) {
		original_points.push_back(std::move(p));
	}
}
