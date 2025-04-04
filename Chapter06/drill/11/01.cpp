/*
	calculator08buggy.cpp

	Helpful comments removed.

	We have inserted 3 bugs that the compiler will catch and 3 that it won't.

	Grammar for input:

	Calculation:
		Statement
		Print
		Quit
		Calculation Statement
	Statement:
		Declaration
		Expression
	Expression:
		Term
		Expression "+" Term
		Expression "-" Term
	Term:
		Primary
		Term "*" Primary
		Term "/" Primary
	Primary:
		Number
		Name
		"(" Expression ")"
		"-" Primary
		"sqrt" "(" Expression ")"
		"pow" "(" Expression "," int(Expression) ")"
	Number:
		floating-point-number
	Name:
		alphanumeric sequence of characters
	Print:
		";"
	Quit:
		"quit"
	Declaration:
		"let" Name "=" Expression
*/

#include "../../../utils/PPP2code/std_lib_facilities.h"
#include <cmath>

struct Token {
	char kind;
	double value;
	string name;
	Token(char ch) :kind(ch), value(0) { }
	Token(char ch, double val) :kind(ch), value(val) { }
	Token(char ch, string s) :kind(ch), name(s) { }
};

class Token_stream {
	bool full;
	Token buffer;
public:
	Token_stream() :full(0), buffer(0) { }

	Token get();
	void unget(Token t) { buffer = t; full = true; }

	void ignore(char);
};

// Token kinds
const char let = 'L';
const char quit = 'Q';
const char print = ';';
const char number = '8';
const char name = 'a';
constexpr char square = 's';
constexpr char power = 'p';
constexpr char declkey = '#';
const std::string quitkey = "exit";

Token Token_stream::get()
{	// read characters from cin to compose a Token
	if (full) { full = false; return buffer; }
	char ch;
	cin >> ch;
	switch (ch) {
	case ',':
	case '(':
	case ')':
	case '+':
	case '-':
	case '*':
	case '/':
	case '%':
	case ';':
	case '=':	// let each character represent itself
		return Token(ch);
	case declkey:
		return Token{let};
	case '.':
	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':	// floating-point literal
	{	cin.unget();
	double val;
	cin >> val;
	return Token(number, val);
	}
	default:
		if (isalpha(ch)) {	// Check for strings
			string s;
			s += ch;
			while (cin.get(ch) && (isalpha(ch) || isdigit(ch))) s += ch;
			cin.unget();
			if (s == quitkey) return Token(quit);
			if (s == "sqrt") return Token(square);
			if (s == "pow") return Token(power);
			return Token(name, s);
		}
		error("Bad token");
	}
}

void Token_stream::ignore(char c)
{	
	if (full && c == buffer.kind) {
		full = false;
		return;
	}
	full = false;

	char ch;
	while (cin >> ch)
		if (ch == c) return;
}

struct Variable {
	string name;
	double value;
	Variable(string n, double v) :name(n), value(v) { }
};

vector<Variable> names;

double get_value(string s)
{	// Get a declared variable's value
	for (int i = 0; i < names.size(); ++i)
		if (names[i].name == s) return names[i].value;
	error("get: undefined name ", s);
}

void set_value(string s, double d)
{	// Set a declared variable's value
	for (int i = 0; i < names.size(); ++i)
		if (names[i].name == s) {
			names[i].value = d;
			return;
		}
	error("set: undefined name ", s);
}

bool is_declared(string s)
{	// Check if name is declared
	for (int i = 0; i < names.size(); ++i)
		if (names[i].name == s) return true;
	return false;
}

Token_stream ts;

double expression();

double primary()
{	// Handle (), sqrt(), pow(), unary -, numbers and names
	Token t = ts.get();
	switch (t.kind) {
	case '(':
	{	double d = expression();
	t = ts.get();
	if (t.kind != ')') error("'(' expected");
	return d;
	}
	case '-':
		return -primary();
	case number:
		return t.value;
	case name:
		return get_value(t.name);
	case square:
	{
		t = ts.get();
		if (t.kind != '(')
			error("'(' expected");
		double d = expression();
		if (d < 0)
			error("negative square");
		t = ts.get();
		if (t.kind != ')')
			error("')' expected");
		return std::sqrt(d);
	}
	case power:
	{
		t = ts.get();
		if (t.kind != '(')
			error("'(' expected");
		double d = expression();
		t = ts.get();
		if (t.kind != ',')
			error("',' expected");
		int p = narrow_cast<int>(expression());
		t = ts.get();
		if (t.kind != ')')
			error("')' expected");
		if (p == 0)
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
		error("primary expected");
	}
}

double term()
{	// Handle *, /
	double left = primary();
	while (true) {
		Token t = ts.get();
		switch (t.kind) {
		case '*':
			left *= primary();
			break;
		case '/':
		{	double d = primary();
		if (d == 0) error("divide by zero");
		left /= d;
		break;
		}
		default:
			ts.unget(t);
			return left;
		}
	}
}

double expression()
{	// Handle +, -
	double left = term();
	while (true) {
		Token t = ts.get();
		switch (t.kind) {
		case '+':
			left += term();
			break;
		case '-':
			left -= term();
			break;
		default:
			ts.unget(t);
			return left;
		}
	}
}

double declaration()
{	// Handle variable declaration
	Token t = ts.get();
	if (t.kind != 'a') error("name expected in declaration");
	string name = t.name;
	if (is_declared(name)) error(name, " declared twice");
	Token t2 = ts.get();
	if (t2.kind != '=') error("= missing in declaration of ", name);
	double d = expression();
	names.push_back(Variable(name, d));
	return d;
}

double statement()
{	// Handle declarations and expressions
	Token t = ts.get();
	switch (t.kind) {
	case let:
		return declaration();
	default:
		ts.unget(t);
		return expression();
	}
}

// Declare and define a variable with a given value
double define_name(string var, double val) {
	if (is_declared(var))
		error(var, " declared twice");
	names.push_back(Variable{var, val});
	return val;
}

void clean_up_mess()
{
	ts.ignore(print);
}

// Printed strings
const string prompt = "> ";	// prompt for reading
const string result = "= ";	// for printing the result

void calculate()
{	// Expression evaluation loop
	while (true) try {
		cout << prompt;
		Token t = ts.get();
		while (t.kind == print)
			t = ts.get();
		if (t.kind == quit)
			return;
		ts.unget(t);
		cout << result << statement() << endl;
	}
	catch (runtime_error& e) {
		cerr << e.what() << endl;
		clean_up_mess();
	}
}

int main()

try {
	define_name("k", 1000);
	calculate();
	return 0;
}
catch (exception& e) {
	cerr << "exception: " << e.what() << endl;
	char c;
	while (cin >> c && c != ';');
	return 1;
}
catch (...) {
	cerr << "exception\n";
	char c;
	while (cin >> c && c != ';');
	return 2;
}
