#include "Token_stream.h"

// Compose a Token
Token Token_stream::get() {
	if (full) {
		full = false;
		return buffer;
	}
	char c;
	while (stream.get(c) && std::isspace(c))	// Read until read character is not whitespace
		if (c == '\n')
			return Token{tprint};
	if (!stream)
		return Token{tnone};
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
	case ',':	// Let each character represent itself
		return Token{c};
	case '.':
	case '0': case '1': case '2': case '3': case '4':
	case '5': case '6': case '7': case '8': case '9':	// floating-point numbers
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
			bool can_be_name = true;
			// Read alphanumeric and underscore characters
			while (stream.get(c) && (std::isalnum(c) || c == '_' || c == '.')) {
				if (c == '.')
					can_be_name = false;
				s += c;
			}
			stream.putback(c);
			if (s == khelp)	// Help keyword
				return Token{thelp};
			if (s == kquit)	// Quit keyword
				return Token{tquit};
			if (s == kdecl)	// Variable declaration keyword
				return Token{tdecl};
			if (s == kconstdecl)	// Const declaration keyword
				return Token{tconstdecl};
			if (s == ksqrt)	// Square root keyword
				return Token{tsqrt};
			if (s == kpow)	// Power keyword
				return Token{tpow};
			if (s == kfloor)	// Floor keyword
				return Token{tfloor};
			if (s == kfrom)
				return Token{tfrom};
			if (s == kto)
				return Token{tto};
			if (s == kclose)
				return Token{tclose};
			if (can_be_name)
				return Token{tname, s};	// Name
			return Token{tfilename, s};
		}
		throw std::runtime_error("bad token");
	}
	}
}

// Fill buffer
void Token_stream::putback(Token t) {
	if (full)
		throw std::runtime_error("buffer full");
	full = true;
	buffer = t;
}

// Ignore input up to and including c
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
