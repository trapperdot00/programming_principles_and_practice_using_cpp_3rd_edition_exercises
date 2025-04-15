#ifndef PERSON_H
#define PERSON_H

#include <string>
#include <iostream>

class Person {
public:
	Person() {}
	Person(const std::string& s, int i)
		: n{s}, a{i} {}

	std::string name() const { return n; }
	int age() const { return a; }
private:
	std::string n;
	int a;
};

std::istream& operator>>(std::istream&, Person&);
std::ostream& operator<<(std::ostream&, const Person&);

#endif
