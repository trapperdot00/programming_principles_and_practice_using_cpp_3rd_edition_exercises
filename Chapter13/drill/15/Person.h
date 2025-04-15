#ifndef PERSON_H
#define PERSON_H

#include <string>
#include <iostream>

struct Person {
	std::string name;
	int age;
};

std::istream& operator>>(std::istream&, Person&);
std::ostream& operator<<(std::ostream&, const Person&);

#endif
