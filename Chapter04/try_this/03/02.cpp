#include <iostream>
#include <stdexcept>

int area(int length, int width) {
	if (length <= 0 || width <= 0)
		return -1;
	return length * width;
}

int framed_area(int x, int y) {
	constexpr int frame_width = 2;
	if (x - frame_width <= 0 || y - frame_width <= 0)
		return -1;
	return area(x - frame_width, y - frame_width);
}

int f(int x, int y, int z) {
	int area1 = area(x, y);
	std::cout << area1 << '\n';
	if (area1 <= 0)
		throw std::runtime_error("non-positive area");
	
	int area2 = framed_area(1, z);
	std::cout << area2 << '\n';
	if (area2 <= 0)
		throw std::runtime_error("non-positive area");
	
	int area3 = framed_area(y, z);
	std::cout << area3 << '\n';
	if (area3 <= 0)
		throw std::runtime_error("non-positive area");

	double ratio = double(area1)/area3;
	std::cout << ratio << '\n';
	return 0;
}

int main() {
	int val1 = 0;
	int val2 = 0;
	int val3 = 0;
	std::cin >> val1 >> val2 >> val3;
	f(val1, val2, val3);
}
