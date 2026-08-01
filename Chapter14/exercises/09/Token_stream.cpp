#include "Token_stream.hpp"

#include <cctype>
#include <string>
#include <stdexcept>

Token Token_stream::get() {
	if (full) {
		full = false;
		return buffer;
	}
	char c;
	while (stream.get(c) && std::isspace(c))
		if (c == '\n')
			return Token{tprint};
	switch (c) {
	case kprint:
		return Token{tprint};
	case '+':
	case '-':
	case '*':
	case '/':
	case '%':
	case '(':
	case ')':
	case '=':
	case ',':
		return Token{c};
	case '.':
	case '0': case '1': case '2': case '3': case '4':
	case '5': case '6': case '7': case '8': case '9':
	{
		stream.putback(c);
		double d = 0.0;
		stream >> d;
		return Token{numeric, d};
	}
	default:
	{
		if (std::isalpha(c) || c == '_') {
			std::string s;
			s += c;
			while (stream.get(c) && (std::isalpha(c) || std::isdigit(c) || c == '_'))
				s += c;
			stream.putback(c);
			if (s == khelp)
				return Token{thelp};
			if (s == kquit)
				return Token{tquit};
			if (s == kdecl)
				return Token{tdecl};
			if (s == kconstdecl)
				return Token{tconstdecl};
			if (s == ksqrt)
				return Token{tsqrt};
			if (s == kpow)
				return Token{tpow};
			if (s == kfloor)
				return Token{tfloor};
			return Token{tname, s};
		}
		throw std::runtime_error("bad token");
	}
	}
}

void Token_stream::putback(Token t) {
	if (full)
		throw std::runtime_error("buffer full");
	full = true;
	buffer = t;
}

void Token_stream::ignore(char c) {
	if (full && buffer.kind == c) {
		full = false;
		return;
	}
	full = false;
	char ch = '\0';
	while (stream >> ch)
		if (ch == c)
			return;
}
