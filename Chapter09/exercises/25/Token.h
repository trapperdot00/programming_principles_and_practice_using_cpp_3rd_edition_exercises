#ifndef TOKEN_H
#define TOKEN_H

#include <string>

struct Token {
	Token(char c) : kind(c) {}
	Token(char c, double d) : kind(c), val(d) {}
	Token(char c, std::string s) : kind(c), name(s) {}

	char kind;
	double val;
	std::string name;
};

#endif
