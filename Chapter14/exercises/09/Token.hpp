#ifndef TOKEN_HPP
#define TOKEN_HPP

#include <string>

struct Token {
	Token(char c) : kind(c) {}
	Token(char c, double d) : kind(c), val(d) {}
	Token(char c, std::string s) : kind(c), name(s) {}

	char kind;
	double val;
	std::string name;
};

// Token identifiers
constexpr char numeric    = '0';
constexpr char tprint     = ';';
constexpr char tquit      = 'q';
constexpr char thelp      = 'h';
constexpr char tdecl      = 'd';
constexpr char tconstdecl = 'c';
constexpr char tname      = 'n';
constexpr char tsqrt      = 's';
constexpr char tpow       = 'p';
constexpr char tfloor     = 'f';

// Keywords
constexpr char kprint            = ';';
constexpr std::string kquit      = "quit";
constexpr std::string khelp      = "help";
constexpr std::string kdecl      = "let";
constexpr std::string kconstdecl = "const";
constexpr std::string ksqrt      = "sqrt";
constexpr std::string kpow       = "pow";
constexpr std::string kfloor     = "floor";

// Printables
constexpr std::string prompt = "> ";
constexpr std::string result = "= ";

#endif
