#ifndef MULTIPLICATION_HPP
#define MULTIPLICATION_HPP

#include "BinaryExpression.hpp"

class Multiplication : public BinaryExpression
{
public:
	using BinaryExpression::BinaryExpression;
	double evaluate(double x) const override
	{
		return get_lhs()->evaluate(x) * get_rhs()->evaluate(x);
	}
};

#endif
