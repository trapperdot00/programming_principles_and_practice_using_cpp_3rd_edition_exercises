/*	Basic calculator program, input from cin, output to cout
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

#include <iostream>
#include <string>
#include <stdexcept>
#include <cctype>
#include <vector>
#include <cmath>

// Token identifiers
constexpr char numeric = '0';
constexpr char tprint = ';';
constexpr char tquit = 'q';
constexpr char thelp = 'h';
constexpr char tdecl = 'd';
constexpr char tconstdecl = 'c';
constexpr char tname = 'n';
constexpr char tsqrt = 's';
constexpr char tpow = 'p';

// Keywords
constexpr char kprint = ';';
constexpr std::string kquit = "quit";
constexpr std::string khelp = "help";
constexpr std::string kdecl = "let";
constexpr std::string kconstdecl = "const";
constexpr std::string ksqrt = "sqrt";
constexpr std::string kpow = "pow";

// Printables
constexpr std::string prompt = "> ";
constexpr std::string result = "= ";

struct Token {
	Token(char c) : kind(c) {}
	Token(char c, double d) : kind(c), val(d) {}
	Token(char c, std::string s) : kind(c), name(s) {}

	char kind;
	double val;
	std::string name;
};

class Token_stream {
public:
	Token_stream() : full(false), buffer(0) {}
	Token get();
	void putback(Token);
	void ignore(char);
private:
	bool full;
	Token buffer;
};

struct Variable {
	Variable(std::string s, double d, bool c) : name(s), value(d), constant(c) {}
	std::string name;
	double value;
	bool constant;
};

// Holds all variables in a vector
class Symbol_table {
public:
	double get(const std::string&) const;
	void set(const std::string&, double);
	bool is_declared(const std::string&) const;
	double declare(const std::string&, double, bool);
private:
	std::vector<Variable> var_table;
} symbols;	// Create a global object

// Get variable's value by its name
double Symbol_table::get(const std::string& name) const {
	for (const Variable& v : var_table)
		if (v.name == name)
			return v.value;
	throw std::runtime_error("trying to read undefined variable " + name);
}

// Assign new value to an already declared variable
void Symbol_table::set(const std::string& name, double value) {
	for (Variable& v : var_table)
		if (v.name == name) {
			if (v.constant)
				throw std::runtime_error("trying to assign to constant");
			v.value = value;
			return;
		}
	throw std::runtime_error("trying to write undefined variable " + name);
}

// Check if a variable with a given name is already declared
bool Symbol_table::is_declared(const std::string& name) const {
	for (const Variable& v : var_table)
		if (v.name == name)
			return true;
	return false;
}

// Declare a new variable with a name, value and a constant qualifier
double Symbol_table::declare(const std::string& name, double value, bool constant) {
	if (is_declared(name))
		throw std::runtime_error(name + " declared twice");
	var_table.emplace_back(name, value, constant);
	return value;
}

template <typename T1, typename T2>
T1 narrow(T2);

// Grammar units
double statement();
double declaration(Token);
double expression();
double term();
double primary();
void calculate();

// Compose a Token
Token Token_stream::get() {
	if (full) {
		full = false;
		return buffer;
	}
	char c;
	while (std::cin.get(c) && std::isspace(c))	// Read until read character is not whitespace
		if (c == '\n')
			return Token{tprint};
	switch (c) {
	case kprint:
		return Token{tprint};
	case '+':
	case '-':
	case '*':
	case '/':
	case '%':
	case '(':
	case ')':
	case '=':
	case ',':	// Let each character represent itself
		return Token{c};
	case '.':
	case '0': case '1': case '2': case '3': case '4':
	case '5': case '6': case '7': case '8': case '9':	// Floating-point number
	{
		std::cin.putback(c);
		double d = 0.0;
		std::cin >> d;
		return Token{numeric, d};
	}
	default:
	{
		if (std::isalpha(c) || c == '_') {
			std::string s;
			s += c;
			// Read alphanumeric and underscore characters
			while (std::cin.get(c) && (std::isalpha(c) || std::isdigit(c) || c == '_'))
				s += c;
			std::cin.putback(c);
			if (s == khelp)	// Help keyword
				return Token{thelp};
			if (s == kquit)	// Quit keyword
				return Token{tquit};
			if (s == kdecl)	// Variable declaration keyword
				return Token{tdecl};
			if (s == kconstdecl)	// Const declaration keyword
				return Token{tconstdecl};
			if (s == ksqrt)	// Square root keyword
				return Token{tsqrt};
			if (s == kpow)	// Power keyword
				return Token{tpow};
			return Token{tname, s};	// Name
		}
		throw std::runtime_error("bad token");
	}
	}
}

// Fill buffer
void Token_stream::putback(Token t) {
	if (full)
		throw std::runtime_error("buffer full");
	full = true;
	buffer = t;
}

// Ignore input up to and including c
void Token_stream::ignore(char c) {
	if (full && buffer.kind == c) {
		full = false;
		return;
	}
	full = false;
	char ch = '\0';
	while (std::cin >> ch)
		if (ch == c)
			return;
}

Token_stream ts;	// Global Token_stream object

// Type-safe narrowing function: error on data-loss
template <typename T1, typename T2>
T1 narrow(T2 t) {
	T1 ret = t;
	if (ret != t)
		throw std::runtime_error("narrow error");
	return ret;
}

// Handle declarations and expressions
double statement() {
	Token t = ts.get();
	switch (t.kind) {
	case tdecl:
	case tconstdecl:
		return declaration(t);
	default:		
		ts.putback(t);
		return expression();
	}
}

double declaration(Token t) {
	Token t1 = ts.get();
	if (t1.kind != tname)
		throw std::runtime_error("name expected after declaration keyword");
	Token t2 = ts.get();
	if (t2.kind != '=')
		throw std::runtime_error("'=' expected after variable declaration");
	double value = expression();
	symbols.declare(t1.name, value, t.kind==tconstdecl);
	return value;
}

// Handle +, -
double expression() {
	double left = term();
	Token t = ts.get();
	while (true) {
		switch (t.kind) {
		case '+':
			left += term();
			t = ts.get();
			break;
		case '-':
			left -= term();
			t = ts.get();
			break;
		default:
			ts.putback(t);
			return left;
		}
	}
}

// Handle *, /, %
double term() {
	double left = primary();
	Token t = ts.get();
	while (true) {
		switch (t.kind) {
		case '*':
			left *= primary();
			t = ts.get();
			break;
		case '/':
			left /= primary();
			t = ts.get();
			break;
		case '%':
		{
			double d = primary();
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

// Handle (), pow(), sqrt(), unary -, unary +, numbers, names and assignment
double primary() {
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
		double rhs = expression();
		symbols.set(t.name, rhs);
		return rhs;
	}
	case '+':
		return primary();
	case '-':
		return -primary();
	case '(':
	{
		double d = expression();
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
		double d = expression();
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
		double d = expression();
		t = ts.get();
		if (t.kind != ',')
			throw std::runtime_error("',' expected");
		int p = narrow<int>(expression());
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
	default:
		throw std::runtime_error("primary expected");
	}
}

// Reset Token_stream to a valid state
void clean_up_mess() {
	ts.ignore(kprint);
}

void print_help() {
	constexpr const char* msg = "Supported operations: + - * / % () sqrt() pow()"
		"\nDeclare variables using 'let var = expression'"
		"\nDeclare constants using 'const pi = expression'"
		"\nCalculate using ';' or entering a newline"
		"\nShow help page using 'help'"
		"\nQuit using 'quit'";
	std::cout << msg << '\n';
}

// Statement evaluation loop
void calculate() {
	while (std::cin) try {
		std::cout << prompt;
		Token t = ts.get();
		while (t.kind == tprint)
			t = ts.get();
		switch (t.kind) {
		case tquit:
			return;
		case thelp:
			print_help();
			break;
		default:
			ts.putback(t);
			std::cout << result << statement() << '\n';
		}
	} catch (std::exception& e) {
		std::cerr << e.what() << '\n';
		clean_up_mess();
	}
}

int main()
{
	calculate();
}
