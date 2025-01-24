#include "Name_pair.h"

void Name_pair::read() {
	std::cin >> n >> a;
}

std::ostream& operator<<(std::ostream& os, const Name_pair& n) {
	return os << n.name() << ":\t" << n.age();
}

bool operator==(const Name_pair& lhs, const Name_pair& rhs) {
	return lhs.name() == rhs.name()
		&& lhs.age() == rhs.age();
}

bool operator!=(const Name_pair& lhs, const Name_pair& rhs) {
	return !(lhs == rhs);
}

bool operator<(const Name_pair& lhs, const Name_pair& rhs) {
	return lhs.name() < rhs.name();
}
