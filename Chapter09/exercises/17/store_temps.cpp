#include <string>
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <random>
#include <chrono>

struct Reading {
	int hour;
	double temperature;
};

std::ostream& operator<<(std::ostream& os, const Reading& rhs) {
	return os << rhs.hour << ' ' << rhs.temperature;
}

Reading random_reading() {
	// Seed random engine with current time
	static std::default_random_engine e(
		std::chrono::steady_clock::now().time_since_epoch().count()
	);

	// For hours 0 - 23
	static std::uniform_int_distribution<int> i_dist(0, 23);

	// For temperatures in fahrenheit, mean value of 59°F,
	// with a standard deviation of 8°F
	static std::normal_distribution<double> d_dist(59, 8);

	// Initialize Reading to random values
	return Reading{i_dist(e), d_dist(e)};
}

int main() {
	constexpr size_t reading_count = 100;

	const std::string filename = "raw_temps.txt";
	std::ofstream ofs{filename};
	if (!ofs)
		throw std::runtime_error{"can't open " + filename + " for writing"};

	for (size_t i = 0; i < reading_count; ++i) {
		ofs << random_reading() << '\n';
	}
}
