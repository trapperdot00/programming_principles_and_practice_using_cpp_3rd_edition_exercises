#ifndef PARAMETER_PARSER_HPP
#define PARAMETER_PARSER_HPP

#include "Token_stream.hpp"
#include "Expression.hpp"
#include <memory>

class Parameter_parser
{
public:
	std::unique_ptr<Expression> operator()(Token_stream ts);
private:
	static std::unique_ptr<Expression> expression(Token_stream& ts);
	static std::unique_ptr<Expression> term(Token_stream& ts);
	static std::unique_ptr<Expression> primary(Token_stream& ts);
};

#endif
