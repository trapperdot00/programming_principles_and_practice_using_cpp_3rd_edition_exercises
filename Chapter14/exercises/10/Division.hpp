#ifndef DIVISION_HPP
#define DIVISION_HPP

#include "BinaryExpression.hpp"

class Division : public BinaryExpression
{
public:
	using BinaryExpression::BinaryExpression;
	double evaluate(double x) const override
	{
		return get_lhs()->evaluate(x) / get_rhs()->evaluate(x);
	}
};

#endif
