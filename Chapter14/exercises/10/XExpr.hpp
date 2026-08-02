#ifndef XEXPR_HPP
#define XEXPR_HPP

#include "Expression.hpp"

class XExpr : public Expression
{
public:
	double evaluate(double x) const override { return x; }
};

#endif
