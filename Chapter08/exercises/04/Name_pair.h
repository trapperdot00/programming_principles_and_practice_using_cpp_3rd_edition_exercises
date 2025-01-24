#ifndef NAME_PAIR_H
#define NAME_PAIR_H

#include <string>
#include <utility>
#include <iostream>
#include <stdexcept>

class Name_pair {
public:
	Name_pair() {}
	Name_pair(const std::string& s, double d)
		: n(s), a(d) {}
	Name_pair(std::string&& s, double d)
		: n(std::move(s)), a(d) {}
	void read();

	std::string name() const { return n; }
	double age() const { return a; }
private:
	std::string n;
	double a{};
};

std::ostream& operator<<(std::ostream&, const Name_pair&);
bool operator==(const Name_pair&, const Name_pair&);
bool operator!=(const Name_pair&, const Name_pair&);
bool operator<(const Name_pair&, const Name_pair&);

#endif
