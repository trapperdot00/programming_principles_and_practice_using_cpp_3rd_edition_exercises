#include <string>
#include <fstream>
#include <stdexcept>
#include <random>
#include <chrono>
#include <array>

#include "Reading.h"

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

	// For temperature scales
	static const std::array<char, 2> temp_scales = {'f', 'c'};
	static std::uniform_int_distribution<size_t> t_dist(0, temp_scales.size() - 1);

	// Generate random values
	int hour = i_dist(e);
	double temp = d_dist(e);
	char scale = temp_scales[t_dist(e)];

	// We generate temperatures in fahrenheit, we have to convert it to celsius
	if (scale == 'c')
		temp = f_to_c(temp);

	// Initialize Reading to random values
	return Reading{hour, temp, scale};
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
