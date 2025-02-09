#include "Reading.h"

std::ostream& operator<<(std::ostream& os, const Reading& rhs) {
	return os << rhs.hour << ' ' << rhs.temperature;
}

std::istream& operator>>(std::istream& is, Reading& rhs) {
	int hour = 0;
	double temp = 0.0;
	if (is >> hour >> temp) {
		if (hour >= 0 && hour <= 23)
			rhs = Reading{hour, temp};
		else
			is.clear(std::ios::failbit);
	}
	return is;
}

bool compare_temp(const Reading& lhs, const Reading& rhs) {
	return lhs.temperature < rhs.temperature;
}
