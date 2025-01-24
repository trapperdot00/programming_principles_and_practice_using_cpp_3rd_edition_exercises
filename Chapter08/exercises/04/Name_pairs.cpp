#include "Name_pairs.h"

// Read name-age pairs
void Name_pairs::read() {
	std::cout << "Enter name-age pairs: ";
	Name_pair temp;
	temp.read();
	while (std::cin) {
		np.push_back(std::move(temp));
		temp.read();
	}
}

// Sort elements based on the ordering of name
void Name_pairs::sort() {
	std::sort(np.begin(), np.end());
}

std::ostream& operator<<(std::ostream& os, const Name_pairs& n) {
	for (size_t i = 0; i < n.size(); ++i) {
		os << n[i] << '\n';
	}
	return os;
}

bool operator==(const Name_pairs& lhs, const Name_pairs& rhs) {
	if (lhs.size() != rhs.size())
		return false;
	for (size_t i = 0; i < lhs.size(); ++i) {
		if (lhs[i] != rhs[i])
			return false;
	}
	return true;
}
bool operator!=(const Name_pairs& lhs, const Name_pairs& rhs) {
	return !(lhs == rhs);
}
