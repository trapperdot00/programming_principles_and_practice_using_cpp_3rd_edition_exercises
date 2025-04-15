#ifndef PERSON_H
#define PERSON_H

#include <string>
#include <iostream>
#include <stdexcept>

class Person {
public:
	Person() {}
	Person(const std::string& s1, const std::string& s2, int i)
		: fn{s1}, ln{s2}, a{i}
	{
		static const std::string illegal{";:\"'[]*&^%$#@!"};
		if (fn.find_first_of(illegal) != std::string::npos)
			throw std::runtime_error{"first name contains invalid characters"};
		if (ln.find_first_of(illegal) != std::string::npos)
			throw std::runtime_error{"last name contains invalid characters"};
		if (a < 0 || a > 149)
			throw std::runtime_error{"invalid age"};
	}

	std::string first_name() const { return fn; }
	std::string last_name() const { return ln; }
	int age() const { return a; }
private:
	std::string fn;
	std::string ln;
	int a;
};

std::istream& operator>>(std::istream&, Person&);
std::ostream& operator<<(std::ostream&, const Person&);

#endif
