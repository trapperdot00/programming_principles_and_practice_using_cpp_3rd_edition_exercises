#ifndef EXPRESSION_HPP
#define EXPRESSION_HPP

class Expression
{
public:
	virtual double evaluate(double x) const = 0;
	virtual ~Expression() = default;
};

#endif
