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
	case 'M': case 'D': case 'C': case 'L': case 'X':
	case 'V': case 'I':
	{	// Roman numerals
		stream.putback(c);
		std::string s;
		stream >> s;
		return Token{roman, roman_to_int(s)};
	}
	default:
	{
		if (std::isalpha(c) || c == '_') {
			std::string s;
			s += c;
			// Read alphanumeric and underscore characters
			while (stream.get(c) && (std::isalpha(c) || std::isdigit(c) || c == '_'))
				s += c;
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
			return Token{tname, s};	// Name
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
