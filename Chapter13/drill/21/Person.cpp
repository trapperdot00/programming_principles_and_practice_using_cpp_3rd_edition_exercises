#include "Person.h"

std::istream& operator>>(std::istream& is, Person& rhs) {
	std::string first_name;
	std::string last_name;
	int age = 0;
	if (is >> first_name >> last_name >> age)
		rhs = Person{first_name, last_name, age};
	return is;
}

std::ostream& operator<<(std::ostream& os, const Person& rhs) {
	return os << rhs.first_name()
		<< ' '
		<< rhs.last_name()
		<< ' '
		<< rhs.age();
}
