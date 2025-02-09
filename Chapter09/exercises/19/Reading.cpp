#include "Reading.h"

std::ostream& operator<<(std::ostream& os, const Reading& rhs) {
	return os << rhs.hour << ' ' << rhs.temperature << ' ' << rhs.scale;
}

std::istream& operator>>(std::istream& is, Reading& rhs) {
	int hour = 0;
	double temp = 0.0;
	char rep = 0;
	if (is >> hour >> temp >> rep) {
		if (hour >= 0 && hour <= 23 && (rep == 'f' || rep == 'c')) {
			// Change scale to fahrenheit
			if (rep == 'c')
				temp = c_to_f(temp);
			rep = 'f';
			rhs = Reading{hour, temp, rep};
		} else
			is.clear(std::ios::failbit);
	}
	return is;
}

bool compare_temp(const Reading& lhs, const Reading& rhs) {
	// Bring the temperatures to a common scale: fahrenheit
	double ltemp = lhs.temperature;
	if (lhs.scale == 'c')
		ltemp = c_to_f(ltemp);
	double rtemp = rhs.temperature;
	if (rhs.scale == 'c')
		rtemp = c_to_f(rtemp);
	return ltemp < rtemp;
}

double f_to_c(double f) {
	return (f - 32) * (double(5) / 9);
}

double c_to_f(double c) {
	return c * (double(9) / 5) + 32;
}
