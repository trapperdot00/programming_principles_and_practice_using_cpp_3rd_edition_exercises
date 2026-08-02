#ifndef UNARYMINUS_HPP
#define UNARYMINUS_HPP

#include "Expression.hpp"
#include <memory>
#include <utility>

class UnaryMinus : public Expression
{
public:
	UnaryMinus(std::unique_ptr<Expression> expr) :
		expr_{std::move(expr)}
	{}
	double evaluate(double x) const override
	{
		return -expr_->evaluate(x);
	}
private:
	std::unique_ptr<Expression> expr_;
};

#endif
