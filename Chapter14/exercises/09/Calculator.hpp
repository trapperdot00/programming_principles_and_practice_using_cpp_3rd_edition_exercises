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
 *		floating-point number
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

#include "Token.hpp"
#include "Token_stream.hpp"
#include "Symbol_table.hpp"
#include <string>

class Calculator
{
public:
    std::string usage();
    double operator()(Token_stream);
private:
    static double primary(Symbol_table&, Token_stream&);
    static double term(Symbol_table&, Token_stream&);
    static double expression(Symbol_table&, Token_stream&);
    static double statement(Symbol_table&, Token_stream&);
    static double declaration(Symbol_table&, Token_stream&, Token);
private:
    Symbol_table sym;
};

#endif
