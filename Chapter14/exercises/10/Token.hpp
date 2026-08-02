#ifndef TOKEN_HPP
#define TOKEN_HPP

struct Token
{
	enum Kind
	{
		none,
		unknown,
		number,
		x,
		plus,
		minus,
		asterisk,
		slash,
		lparen,
		rparen,
	};
	Token() = default;
	Token(Kind k) : kind{k} {}
	Token(double d) : kind{number}, value{d} {}
	Kind kind;
	double value;
};

#endif
