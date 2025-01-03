/*	Expression:
 *		XOR
 *		Expression "|" XOR
 *	
 *	XOR:
 *		AND
 *		XOR "^" AND
 *
 *	AND:
 *		Unary
 *		AND "&" Unary
 *
 *	Unary:
 *		Primary
 *		"!" Primary
 *		"~" Primary
 *	
 *	Primary:
 *		Number
 *		"(" Expression ")"
 *
 *	Number:
 *		integer literal
 *	
 */

#include <iostream>
#include <stdexcept>

class Token {
public:
	Token(char c) : kind(c), value(0) {}
	Token(char c, int v) : kind(c), value(v) {}

	char kind;
	int value;
};
class Token_stream {
public:
	void putback(Token t) {
		if (full)
			throw std::runtime_error("Token_stream buffer full!");
		full = true;
		buffer = t;
	}
	Token get() {
		if (full) {
			full = false;
			return buffer;
		}
		char ch = '\0';
		if (!(std::cin >> ch))
			throw std::runtime_error("No data to read in get()!");
		switch (ch) {
		case ';': case 'q':
		case '(': case ')':
		case '!': case '~': case '&': case '^': case '|':
			return Token{ch};
		case '-':	// Only bitwise operators allowed, - for sign
		case '0': case '1': case '2': case '3': case '4':
		case '5': case '6': case '7': case '8': case '9':
		{
			std::cin.putback(ch);
			int val = 0;
			std::cin >> val;
			return Token{'8', val};
		}
		default:
			throw std::runtime_error("Bad token");
		}
	}
private:
	bool full = false;
	Token buffer = 0;
} ts;

int xor_expression();
int and_expression();
int unary_expression();
int primary_expression();

int expression() {
	int left = xor_expression();
	Token t = ts.get();

	while (true) {
		switch (t.kind) {
		case '|':
			left |= xor_expression();
			t = ts.get();
			break;
		default:
			ts.putback(t);
			return left;
		}
	}
}

int xor_expression() {
	int left = and_expression();
	Token t = ts.get();
	
	while (true) {
		switch (t.kind) {
		case '^':
			left ^= and_expression();
			t = ts.get();
			break;
		default:
			ts.putback(t);
			return left;
		}
	}
}

int and_expression() {
	int left = unary_expression();
	Token t = ts.get();

	while (true) {
		switch (t.kind) {
		case '&':
			left &= unary_expression();
			t = ts.get();
			break;
		default:
			ts.putback(t);
			return left;
		}
	}
}

int unary_expression() {
	Token t = ts.get();
	switch (t.kind) {
	case '(':
		ts.putback(t);
		return primary_expression();
	case '8':
	{
		return t.value;
	}
	case '!':
	{
		int value = primary_expression();
		return !value;
	}
	case '~':
	{
		int value = primary_expression();
		return ~value;
	}
	default:
		throw std::runtime_error("no match in unary!");
	}
}

int primary_expression() {
	Token t = ts.get();
	switch (t.kind) {
	case '(':
	{
		int value = expression();
		t = ts.get();
		if (t.kind != ')')
			throw std::runtime_error("missing ')'!");
		return value;
	}
	case '8':
		return t.value;
	default:
		throw std::runtime_error("primary expected!");
	}
}

int main()
try {
	std::cout << "Bitwise calculator\n"
		"Operators: & | ^ ! ~ ( )\n"
		"Solve using ';'\n"
		"Exit with 'q'\n\n";
	int val = 0;
	while (std::cin) {
		Token t = ts.get();
		if (t.kind == 'q')
			break;
		if (t.kind == ';')
			std::cout << "= " << val << '\n';
		else
			ts.putback(t);
		val = expression();
	}
} catch (std::exception& e) {
	std::cerr << "error: " << e.what() << '\n';
} catch (...) {
	std::cerr << "unknown error!\n";
}
