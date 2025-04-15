#ifndef PERSON_H
#define PERSON_H

#include <string>
#include <iostream>

struct Person {
	Person() {}
	Person(const std::string& s, int i)
		: name{s}, age{i} {}
	std::string name;
	int age;
};

std::istream& operator>>(std::istream&, Person&);
std::ostream& operator<<(std::ostream&, const Person&);

#endif
