#ifndef DAY_H
#define DAY_H

#include <vector>

constexpr int not_a_reading = -7777;

struct Day {
	std::vector<double> temp = std::vector<double>(24, not_a_reading);
};

#endif
