#include "Parameter_parser.hpp"

#include "Number.hpp"
#include "XExpr.hpp"
#include "Addition.hpp"
#include "Subtraction.hpp"
#include "Multiplication.hpp"
#include "Division.hpp"
#include "UnaryMinus.hpp"

#include <stdexcept>
#include <utility>

std::unique_ptr<Expression> Parameter_parser::operator()(Token_stream ts)
{
	return expression(ts);
}

std::unique_ptr<Expression> Parameter_parser::expression(Token_stream& ts)
{
	auto lhs = term(ts);
	Token t;
	while (true)
	{
		t = ts.get();
		switch (t.kind)
		{
			case Token::plus:
			{
				auto rhs = term(ts);
				auto add = std::make_unique<Addition>(
					std::move(lhs),
					std::move(rhs)
				);
				lhs = std::move(add);
				break;
			}
			case Token::minus:
			{
				auto rhs = term(ts);
				auto sub = std::make_unique<Subtraction>(
					std::move(lhs),
					std::move(rhs)
				);
				lhs = std::move(sub);
				break;
			}
			default:
				ts.putback(t);
				return lhs;
		}
	}
}

std::unique_ptr<Expression> Parameter_parser::term(Token_stream& ts)
{
	auto lhs = primary(ts);
	Token t;
	while (true)
	{
		t = ts.get();
		switch (t.kind)
		{
			case Token::asterisk:
			{
				auto rhs = primary(ts);
				auto mul = std::make_unique<Multiplication>(
					std::move(lhs),
					std::move(rhs)
				);
				lhs = std::move(mul);
				break;
			}
			case Token::slash:
			{
				auto rhs = primary(ts);
				auto div = std::make_unique<Division>(
					std::move(lhs),
					std::move(rhs)
				);
				lhs = std::move(div);
				break;
			}
			default:
				ts.putback(t);
				return lhs;
		}
	}
}

std::unique_ptr<Expression> Parameter_parser::primary(Token_stream& ts)
{
	Token t = ts.get();
	switch (t.kind)
	{
		case Token::minus:
			return std::make_unique<UnaryMinus>(expression(ts));
		case Token::number:
			return std::make_unique<Number>(t.value);
		case Token::x:
			return std::make_unique<XExpr>();
		case Token::lparen:
		{
			std::unique_ptr<Expression> expr = expression(ts);
			t = ts.get();
			if (t.kind != Token::rparen)
			{
				throw std::runtime_error{"')' expected"};
			}
			return expr;
		}
		default:
			throw std::runtime_error{"Primary expected"};
	}
}
