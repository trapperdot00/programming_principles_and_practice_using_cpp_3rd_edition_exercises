#ifndef NUMBER_HPP
#define NUMBER_HPP

#include "Expression.hpp"

class Number : public Expression
{
public:
	Number(double value) : num{value} {}
	double evaluate(double) const override { return num; }
private:
	double num;
};

#endif
