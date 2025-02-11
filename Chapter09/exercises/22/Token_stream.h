#ifndef TOKEN_STREAM_H
#define TOKEN_STREAM_H

#include "Token.h"
#include "Keywords.h"
#include "Roman.h"

#include <iostream>
#include <cctype>
#include <stdexcept>

class Token_stream {
public:
	Token_stream(std::istream& is) : full(false), buffer(0), stream(is) {}
	Token_stream() : Token_stream(std::cin) {}
	Token get();
	void putback(Token);
	void ignore(char);
	explicit operator bool() const {	// Return stream's state
		return bool(stream);
	}
private:
	bool full;
	Token buffer;
	std::istream& stream;	// Read from this input stream
};

#endif
