#include "Token_stream.hpp"

#include <cctype>

Token_stream::Token_stream(std::istream& is) :
	stream{is}
{}

Token Token_stream::get()
{
	if (buffer)
	{
		Token t = *buffer;
		buffer = std::nullopt;
		return t;
	}
	char c;
	if (!(stream >> c))
	{
		return Token{Token::none};
	}
	switch (c)
	{
		case '.':
		case '0': case '1': case '2': case '3': case '4':
		case '5': case '6': case '7': case '8': case '9':
		{
			stream.unget();
			double value;
			stream >> value;
			return Token{value};
		}
		case '+':
			return Token{Token::plus};
		case '-':
			return Token{Token::minus};
		case '*':
			return Token{Token::asterisk};
		case '/':
			return Token{Token::slash};
		case '(':
			return Token{Token::lparen};
		case ')':
			return Token{Token::rparen};
		default:
		{
			if (c == 'x' || c == 'X')
			{
				return Token{Token::x};
			}
			return Token{Token::unknown};
		}
	}
}

void Token_stream::putback(Token t)
{
	if (buffer)
	{
		throw buffer_full{};
	}
	buffer = t;
}

Token_stream::operator bool() const
{
	return static_cast<bool>(stream);
}
