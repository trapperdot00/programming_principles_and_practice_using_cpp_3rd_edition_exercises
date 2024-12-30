#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <numeric>

double convert_to_m(double value, const std::string &unit) {
	constexpr double m_per_cm = 0.01;
	constexpr double m_per_in = 0.0254;
	constexpr double m_per_ft = 0.3048;
	
	double factor = 0.0;
	if (unit == "m") {
		factor = 1.0;
	} else if (unit == "cm") {
		factor = m_per_cm;
	} else if (unit == "in") {
		factor = m_per_in;
	} else if (unit == "ft") {
		factor = m_per_ft;
	}
	return value * factor;
}

bool valid_unit(const std::string &unit) {
	return unit == "cm" || unit == "m" || unit == "in" || unit == "ft";
}

int main()
{
	std::vector<double> values_m;
	double val = 0.0;
	std::string unit;	// cm, m, in, ft

	while (std::cin >> val >> unit) {
		if (valid_unit(unit)) {
			double val_m = convert_to_m(val, unit);
			values_m.push_back(val_m);
			std::cout << val_m << "m\n";
		} else
			std::cout << "Invalid unit!\n";
	}
	std::ranges::sort(values_m);

	if (!values_m.empty()) {
		std::cout << "Smallest:\t\t" << values_m[0] << "m\n"
			<< "Largest:\t\t" << values_m[values_m.size()-1] << "m\n"
			<< "Number of values:\t" << values_m.size()
			<< "\nSum:\t\t\t" << std::accumulate(values_m.cbegin(), values_m.cend(), 0.0) << "m\n";
	} else {
		std::cout << "No data!\n";
	}
}
