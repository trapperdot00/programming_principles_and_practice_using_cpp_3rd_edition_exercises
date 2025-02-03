#include <iostream>
#include <cctype>
#include <iomanip>

#include <string>
#include <sstream>

enum class NumBase {
	dec, oct, hex
};

struct Reading {
	int value;
	NumBase base;
};

// TODO: fix this horrible mess!
std::istream& operator>>(std::istream& is, Reading& r) {
	std::string line;
	is >> line;
	std::istringstream istr(line);

	char ch1 = 0;
	if (!(istr >> ch1)) {
		is.clear(std::ios::failbit);
		return is;
	}

	if (ch1 == '-') {
		char ch2 = 0;
		if (!(istr >> ch2)) {
			is.clear(std::ios::failbit);
			return is;
		}
		if (ch2 != '0') {
			if (!std::isdigit(ch2)) {
				is.clear(std::ios::failbit);
				return is;
			}
			istr.unget();
			int val = 0;
			if (!(istr >> val)) {
				is.clear(std::ios::failbit);
				return is;
			}
			r = Reading{-val, NumBase::dec};
		} else {
			char ch3 = 0;
			if (!(istr >> ch3)) {
				r = Reading{0, NumBase::dec};
				return is;
			}
			if (ch3 == 'x') {
				int val = 0;
				if (!(istr >> std::hex >> val >> std::dec)) {
					is.clear(std::ios::failbit);
					return is;
				}
				r = Reading{-val, NumBase::hex};
			} else {
				istr.unget();
				int val = 0;
				if (!(istr >> std::oct >> val >> std::dec)) {
					is.clear(std::ios::failbit);
					return is;
				}
				r = Reading{-val, NumBase::oct};
			}
		}
	} else if (ch1 != '0') {
		if (!std::isdigit(ch1)) {
			is.clear(std::ios::failbit);
			return is;
		}
		istr.unget();
		int val = 0;
		if (!(istr >> val)) {
			is.clear(std::ios::failbit);
			return is;
		}
		r = Reading{val, NumBase::dec};
	} else {
		// ch1 == 0
		char ch2 = 0;
		if (!(istr >> ch2)) {
			r = Reading{0, NumBase::dec};
			return is;
		}
		if (ch2 == 'x') {
			int val = 0;
			if (!(istr >> std::hex >> val >> std::dec)) {
				is.clear(std::ios::failbit);
				return is;
			}
			r = Reading{val, NumBase::hex};
		} else {
			istr.unget();
			int val = 0;
			if (!(istr >> std::oct >> val >> std::dec)) {
				is.clear(std::ios::failbit);
				return is;
			}
			r = Reading{val, NumBase::oct};
		}
	}
	return is;
}

int main() {
	for (Reading r; std::cin >> r; ) {
		std::cout << r.value << '\t' << static_cast<int>(r.base) << '\n';
	}
}
