#ifndef BINARYEXPRESSION_HPP
#define BINARYEXPRESSION_HPP

#include "Expression.hpp"
#include <memory>

class BinaryExpression : public Expression
{
public:
	BinaryExpression(std::unique_ptr<Expression> lhs, std::unique_ptr<Expression> rhs) :
		lhs_{std::move(lhs)}, rhs_{std::move(rhs)}
	{}
protected:
	Expression* get_lhs() const { return lhs_.get(); }
	Expression* get_rhs() const { return rhs_.get(); }
private:
	std::unique_ptr<Expression> lhs_;
	std::unique_ptr<Expression> rhs_;
};
#endif
