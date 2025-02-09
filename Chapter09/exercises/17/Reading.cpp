#include "Reading.h"

std::ostream& operator<<(std::ostream& os, const Reading& rhs) {
	return os << rhs.hour << ' ' << rhs.temperature;
}
