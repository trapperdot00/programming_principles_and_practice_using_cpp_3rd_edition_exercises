#include <iostream>
#include <string>

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
	double sum_m = 0.0;
	int count = 0;
	double smallest_m = 0.0;
	double largest_m = 0.0;
	double val = 0.0;
	std::string unit;	// cm, m, in, ft

	bool first = true;
	while (std::cin >> val >> unit) {
		if (valid_unit(unit)) {
			double val_m = convert_to_m(val, unit);
			if (first) {
				smallest_m = largest_m = val_m;
				first = false;
			} else {
				if (val_m<smallest_m) {
					smallest_m = val_m;
					std::cout << "The smallest so far.\n";
				} else if (val_m>largest_m) {
					largest_m = val_m;
					std::cout << "The largest so far.\n";
				}
			}
			++count;
			sum_m += val_m;
			std::cout << val_m << "m\n";
		} else
			std::cout << "Invalid unit!\n";
	}

	std::cout << "Smallest:\t\t" << smallest_m << "m\n"
		<< "Largest:\t\t" << largest_m << "m\n"
		<< "Number of values:\t" << count
		<< "\nSum:\t\t\t" << sum_m << "m\n";
}
