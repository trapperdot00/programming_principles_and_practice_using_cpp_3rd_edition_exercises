#ifndef TOKEN_STREAM_HPP
#define TOKEN_STREAM_HPP

#include "Token.hpp"
#include <iostream>
#include <optional>

class Token_stream
{
public:
	struct buffer_full{};

	Token_stream(std::istream&);
	Token get();
	void putback(Token t);
	explicit operator bool() const;
private:
	std::istream& stream;
	std::optional<Token> buffer;
};

#endif
