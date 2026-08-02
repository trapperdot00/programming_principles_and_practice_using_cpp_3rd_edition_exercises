#ifndef SUBTRACTION_HPP
#define SUBTRACTION_HPP

#include "BinaryExpression.hpp"

class Subtraction : public BinaryExpression
{
public:
	using BinaryExpression::BinaryExpression;
	double evaluate(double x) const override
	{
		return get_lhs()->evaluate(x) - get_rhs()->evaluate(x);
	}
};

#endif
