#include "Person.h"

std::istream& operator>>(std::istream& is, Person& rhs) {
	std::string name;
	int age = 0;
	if (is >> name >> age)
		rhs = Person{name, age};
	return is;
}

std::ostream& operator<<(std::ostream& os, const Person& rhs) {
	return os << rhs.name() << ' ' << rhs.age();
}
