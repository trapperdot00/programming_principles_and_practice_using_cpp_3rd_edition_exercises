#ifndef KEYWORDS_H
#define KEYWORDS_H

#include <string>

// Token identifiers
constexpr char numeric = '0';
constexpr char roman = 'X';
constexpr char tprint = ';';
constexpr char tquit = 'q';
constexpr char thelp = 'h';
constexpr char tdecl = 'd';
constexpr char tconstdecl = 'c';
constexpr char tname = 'n';
constexpr char tsqrt = 's';
constexpr char tpow = 'p';
constexpr char tfloor = 'f';

// Keywords
constexpr char kprint = ';';
constexpr std::string kquit = "quit";
constexpr std::string khelp = "help";
constexpr std::string kdecl = "let";
constexpr std::string kconstdecl = "const";
constexpr std::string ksqrt = "sqrt";
constexpr std::string kpow = "pow";
constexpr std::string kfloor = "floor";

// Printables
constexpr std::string prompt = "> ";
constexpr std::string result = "= ";

#endif
