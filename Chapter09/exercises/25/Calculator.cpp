#include "Calculator.h"

// Handle declarations and expressions
double statement(Token_stream& ts) {
	Token t = ts.get();
	switch (t.kind) {
	case tdecl:
	case tconstdecl:
		return declaration(ts, t);
	default:		
		ts.putback(t);
		return expression(ts);
	}
}

double declaration(Token_stream& ts, Token t) {
	Token t1 = ts.get();
	if (t1.kind != tname)
		throw std::runtime_error("name expected after declaration keyword");
	Token t2 = ts.get();
	if (t2.kind != '=')
		throw std::runtime_error("'=' expected after variable declaration");
	double value = expression(ts);
	symbols.declare(t1.name, value, t.kind==tconstdecl);
	return value;
}

// Handle +, -
double expression(Token_stream& ts) {
	double left = term(ts);
	Token t = ts.get();
	while (true) {
		switch (t.kind) {
		case '+':
			left += term(ts);
			t = ts.get();
			break;
		case '-':
			left -= term(ts);
			t = ts.get();
			break;
		default:
			ts.putback(t);
			return left;
		}
	}
}

// Handle *, /, %
double term(Token_stream& ts) {
	double left = primary(ts);
	Token t = ts.get();
	while (true) {
		switch (t.kind) {
		case '*':
			left *= primary(ts);
			t = ts.get();
			break;
		case '/':
			left /= primary(ts);
			t = ts.get();
			break;
		case '%':
		{
			double d = primary(ts);
			if (d == 0)
				throw std::runtime_error("%: divide by zero");
			left = std::fmod(left, d);
			t = ts.get();
			break;
		}
		default:
			ts.putback(t);
			return left;
		}
	}
}

// Handle (), pow(), sqrt(), floor(), unary -, unary +, numbers, names and assignment
double primary(Token_stream& ts) {
	Token t = ts.get();
	switch (t.kind) {
	case numeric:
		return t.val;
	case tname:
	{
		Token t2 = ts.get();
		if (t2.kind != '=') {
			ts.putback(t2);
			return symbols.get(t.name);
		}
		double rhs = expression(ts);
		symbols.set(t.name, rhs);
		return rhs;
	}
	case '+':
		return primary(ts);
	case '-':
		return -primary(ts);
	case '(':
	{
		double d = expression(ts);
		t = ts.get();
		if (t.kind != ')')
			throw std::runtime_error("')' expected");
		return d;
	}
	case tsqrt:
	{
		t = ts.get();
		if (t.kind != '(')
			throw std::runtime_error("'(' expected");
		double d = expression(ts);
		t = ts.get();
		if (t.kind != ')')
			throw std::runtime_error("')' expected");
		if (d < 0)
			throw std::runtime_error("negative square");
		return std::sqrt(d);
	}
	case tpow:
	{
		t = ts.get();
		if (t.kind != '(')
			throw std::runtime_error("'(' expected");
		double d = expression(ts);
		t = ts.get();
		if (t.kind != ',')
			throw std::runtime_error("',' expected");
		int p = narrow<int>(expression(ts));
		t = ts.get();
		if (t.kind != ')')
			throw std::runtime_error("')' expected");
		if (!p)
			return 1;
		double old = d;
		if (p > 0) {
			for (int i = 1; i < p; ++i)
				d *= old;
			return d;
		} else {
			for (int i = -1; i > p; --i)
				d *= old;
			return 1/d;
		}
	}
	case tfloor:
	{
		t = ts.get();
		if (t.kind != '(')
			throw std::runtime_error("'(' expected");
		double val = expression(ts);
		t = ts.get();
		if (t.kind != ')')
			throw std::runtime_error("')' expected");
		int cpy = narrow<int>(val);
		if (cpy == val || val >= 0)	// If the floating point number is already floored
			return cpy;
		return cpy - 1;
	}
	default:
		throw std::runtime_error("primary expected");
	}
}

// Reset Token_stream to a valid state
void clean_up_mess(Token_stream& ts) {
	ts.ignore(kprint);
}

void print_help() {
	constexpr const char* msg = "Supported operations: + - * / % () sqrt() pow() floor()"
		"\nDeclare variables using 'let var = expression'"
		"\nDeclare constants using 'const pi = expression'"
		"\nCalculate using ';' or entering a newline"
		"\nShow help page using 'help'"
		"\nQuit using 'quit'";
	std::cout << msg << '\n';
}

// Statement evaluation loop
void calculate(Token_stream& ts, std::ostream& os, bool from_file) {
	while (ts) try {	// Test the stream
		if (!from_file)
			std::cout << prompt;
		Token t = ts.get();
		while (t.kind == tprint)
			t = ts.get();
		switch (t.kind) {
		case tnone:		// Input filestream empty
		case tclose:	// Close function (and any associated file streams with it)
		case tquit:
			return;
		case thelp:
			print_help();
			break;
		case tfrom:
		{	// Read input from file
			Token t2 = ts.get();
			if (t2.kind != tname && t2.kind != tfilename)
				throw std::runtime_error{"filename expected"};
			std::ifstream ifs{t2.name};
			if (!ifs)
				throw std::runtime_error{"can't open " + t2.name + " for reading"};
			// Recursive call: returns when file hits EOF
			Token_stream ts2{ifs};
			calculate(ts2, os, true);
			break;
		}
		case tto:
		{	// Output calculations into file
			Token t2 = ts.get();
			if (t2.kind != tname && t2.kind != tfilename)
				throw std::runtime_error{"filename expected"};
			std::ofstream ofs{t2.name};
			if (!ofs)
				throw std::runtime_error{"can't open " + t2.name + " for writing"};
			calculate(ts, ofs, from_file);
			break;
		}
		default:
			ts.putback(t);
			os << result << statement(ts) << '\n';
		}
	} catch (std::exception& e) {
		os << e.what() << '\n';
		clean_up_mess(ts);
	}
}
