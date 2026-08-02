#ifndef ADDITION_HPP
#define ADDITION_HPP

#include "BinaryExpression.hpp"

class Addition : public BinaryExpression
{
public:
	using BinaryExpression::BinaryExpression;
	double evaluate(double x) const override
	{
		return get_lhs()->evaluate(x) + get_rhs()->evaluate(x);
	}
};

#endif
