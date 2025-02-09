#include <fstream>
#include <stdexcept>
#include <string>
#include <vector>
#include <algorithm>

#include "Reading.h"

auto read_file(const std::string& filename) -> std::vector<Reading> {
	std::ifstream ifs{filename};
	if (!ifs)
		throw std::runtime_error{"can't open " + filename + " for reading"};
	std::vector<Reading> readings;
	for (Reading r; ifs >> r; )
		readings.push_back(r);
	return readings;
}

auto mean_temp(const std::vector<Reading>& vec) -> double {
	if (vec.empty())
		throw std::runtime_error{"empty vector for mean"};
	double sum = 0.0;
	for (const Reading& r : vec)
		sum += r.temperature;
	return sum / vec.size();
}

auto median_temp(std::vector<Reading> vec) -> double {
	if (vec.empty())
		throw std::runtime_error{"empty vector for median"};
	
	// Sort readings based on their temperatures
	std::ranges::sort(vec, compare_temp);
	double middle = vec[vec.size() / 2].temperature;
	// Odd: middle points to the median
	if (vec.size() % 2)
		return middle;
	// Even: the median is the two middle elements' mean
	double middle2 = vec[vec.size() / 2 - 1].temperature;
	return (middle + middle2) / 2;
}

int main() {
	const std::string filename = "raw_temps.txt";

	const std::vector<Reading> readings = read_file(filename);
	std::cout << "Mean temperature: " << mean_temp(readings)
		<< "\nMedian temperature: " << median_temp(readings)
		<< '\n';
}
