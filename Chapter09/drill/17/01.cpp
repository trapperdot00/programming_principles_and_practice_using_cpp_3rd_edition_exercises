#include "Point.h"

#include <string>
#include <vector>
#include <utility>
#include <stdexcept>
#include <fstream>

// Read n amount of points
std::vector<Point> read_points(std::istream& is, size_t n) {
	std::vector<Point> ret;
	for (Point p; ret.size() < n && is >> p; )
		ret.push_back(std::move(p));
	if (ret.size() != n)
		throw std::runtime_error{"Insufficient data"};
	return ret;
}

// To keep file stream to a small scope,
// so that it gets closed as soon as the function returns
std::vector<Point> read_from_file(const std::string& filename, size_t n) {
	std::ifstream ifs{filename};
	return read_points(ifs, n);
}

std::ostream& print_points(std::ostream& os, const std::vector<Point>& v) {
	for (const Point& p : v)
		os << p;
	return os << '\n';
}

// To avoid issues with multiple openings of a file in main
void print_to_file(const std::string& filename, const std::vector<Point>& v) {
	std::ofstream of{filename};
	print_points(of, v);
}

int main() {
	constexpr size_t maxsize = 7;
	const std::string filename = "mydata.txt";

	std::cout << std::format("Enter {} points: ", maxsize);

	// Read points from stdin
	std::vector<Point> original_points = read_points(std::cin, maxsize);
	print_points(std::cout, original_points);
	print_to_file(filename, original_points);

	std::vector<Point> processed_points = read_from_file(filename, maxsize);

	std::cout << "\nOriginal points:\n";
	print_points(std::cout, original_points) << '\n';
	std::cout << "Processed points:\n";
	print_points(std::cout, processed_points);

	if (original_points.size() != processed_points.size() ||
			original_points != processed_points)
		std::cout << "\nSomething's wrong!\n";
}
