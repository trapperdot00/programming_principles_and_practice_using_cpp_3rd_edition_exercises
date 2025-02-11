#include "Roman.h"

#include <iomanip>

int main() {
	Roman r{1};
	do {
		std::cout << "Enter Roman number:\n";
		if (std::cin >> r) {
			std::cout << std::setw(15) << std::left << r
				<< " = " << r.as_int()
				<< '\n';
		}
	} while (std::cin);
}
