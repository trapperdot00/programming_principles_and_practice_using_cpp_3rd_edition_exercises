/*	Basic calculator program, input from any istream, output to cout
 *
 *	Grammar for input:
 *
 *	Calculation:
 *		Statement
 *		Print
 *		Quit
 *		Help
 *		Calculation Statement
 *	Statement:
 *		Declaration
 *		Expression
 *	Expression:
 *		Term
 *		Expression "+" Term
 *		Expression "-" Term
 *	Term:
 *		Primary
 *		Term "*" Primary
 *		Term "/" Primary
 *		Term "%" Primary
 *	Primary:
 *		Number
 *		Name
 *		"-" Primary
 *		"+" Primary
 *		"(" Expression ")"
 *		"sqrt" "(" Expression ")"
 *		"pow" "(" Expression "," int(Expression) ")"
 *		"floor" "(" Expression ")"
 *		Name "=" Expression
 *	Number:
 *		Roman numeral
 *	Name:
 *		sequence of alphanumeric or underscore characters
 *	Print:
 *		";"
 *	Quit:
 *		"quit"
 *	Help:
 *		"help"
 * 	Declaration:
 * 		"let" Name "=" Expression
 * 		"const" Name "=" Expression
 *
 */

#ifndef CALCULATOR_H
#define CALCULATOR_H

#include "Token_stream.h"
#include "Symbol_table.h"

#include <cmath>

// Grammar units
int statement(Token_stream&);
int declaration(Token_stream&, Token);
int expression(Token_stream&);
int term(Token_stream&);
int primary(Token_stream&);
void calculate(Token_stream&);

// Type-safe narrowing function: error on data-loss
template <typename T1, typename T2>
T1 narrow(T2 t) {
	T1 ret = t;
	if (ret != t)
		throw std::runtime_error("narrow error");
	return ret;
}

#endif
