#include "Person.h"

std::istream& operator>>(std::istream& is, Person& rhs) {
	Person p;
	if (is >> p.name >> p.age)
		rhs = p;
	return is;
}

std::ostream& operator<<(std::ostream& os, const Person& rhs) {
	return os << rhs.name << ' ' << rhs.age;
}
