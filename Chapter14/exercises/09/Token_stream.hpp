#ifndef TOKEN_STREAM_HPP
#define TOKEN_STREAM_HPP

#include "Token.hpp"
#include <iostream>

class Token_stream {
public:
	Token_stream(std::istream& is) : stream{is} {}
	Token_stream() = default;

	Token get();
	void putback(Token);
	void ignore(char);
	explicit operator bool() const { return static_cast<bool>(stream); }
private:
	bool full = false;
	Token buffer = 0;
    std::istream& stream;
};

#endif
