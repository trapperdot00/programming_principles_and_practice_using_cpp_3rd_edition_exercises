/*	Basic calculator program
 *	Input from stdin initially, can be changed by user input
 *	Output to stdin by default, can be changed by user input
 *
 *	Grammar for input:
 *
 *	Calculation:
 *		Statement
 *		Print
 *		Quit
 *		Help
 *		File input
 *		File output
 *		Close
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
 *	Filename:
 *		sequence of alphanumeric or underscore or dot characters
 *	Print:
 *		";"
 *	Quit:
 *		"quit"
 *	Help:
 *		"help"
 *	File input:
 *		"from" Filename
 *	File output:
 *		"to" Filename
 *	Close:
 *		"close"
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
#include <fstream>

// Grammar units
double statement(Token_stream&);
double declaration(Token_stream&, Token);
double expression(Token_stream&);
double term(Token_stream&);
double primary(Token_stream&);
void calculate(Token_stream&, std::ostream&, bool = false);

// Type-safe narrowing function: error on data-loss
template <typename T1, typename T2>
T1 narrow(T2 t) {
	T1 ret = t;
	if (ret != t)
		throw std::runtime_error("narrow error");
	return ret;
}

#endif
