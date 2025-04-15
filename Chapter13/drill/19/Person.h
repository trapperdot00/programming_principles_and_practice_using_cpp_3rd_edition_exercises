#ifndef PERSON_H
#define PERSON_H

#include <string>
#include <iostream>
#include <stdexcept>

class Person {
public:
	Person() {}
	Person(const std::string& s, int i)
		: n{s}, a{i}
	{
		static const std::string illegal{";:\"'[]*&^%$#@!"};
		if (n.find_first_of(illegal) != std::string::npos)
			throw std::runtime_error{"name contains invalid characters"};
		if (a < 0 || a > 149)
			throw std::runtime_error{"invalid age"};
	}

	std::string name() const { return n; }
	int age() const { return a; }
private:
	std::string n;
	int a;
};

std::istream& operator>>(std::istream&, Person&);
std::ostream& operator<<(std::ostream&, const Person&);

#endif
