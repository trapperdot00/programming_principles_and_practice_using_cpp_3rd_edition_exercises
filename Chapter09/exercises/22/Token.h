#ifndef TOKEN_H
#define TOKEN_H

#include <string>

struct Token {
	Token(char c) : kind(c) {}
	Token(char c, int i) : kind(c), val(i) {}
	Token(char c, std::string s) : kind(c), name(s) {}

	char kind;
	int val;
	std::string name;
};

#endif
