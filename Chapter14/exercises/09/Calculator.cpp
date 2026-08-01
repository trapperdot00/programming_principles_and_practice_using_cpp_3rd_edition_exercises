#include "Calculator.hpp"
#include "Token.hpp"
#include "Token_stream.hpp"
#include "Symbol_table.hpp"

#include <stdexcept>
#include <cmath>
#include <string>

template <typename T1, typename T2>
T1 narrow(T2 t) {
    T1 ret = t;
    if (ret != t)
        throw std::runtime_error("narrow error");
    return ret;
}

double Calculator::statement(Symbol_table& sym, Token_stream& ts) {
    Token t = ts.get();
    switch (t.kind) {
    case tdecl:
    case tconstdecl:
        return declaration(sym, ts, t);
    default:
        ts.putback(t);
        return expression(sym, ts);
    }
}

double Calculator::declaration(Symbol_table& sym, Token_stream& ts, Token t) {
    Token t1 = ts.get();
    if (t1.kind != tname)
        throw std::runtime_error("name expected after declaration keyword");
    Token t2 = ts.get();
    if (t2.kind != '=')
        throw std::runtime_error("'=' expected after variable declaration");
    double value = expression(sym, ts);
    sym.declare(t1.name, value, t.kind == tconstdecl);
    return value;
}

double Calculator::expression(Symbol_table& sym, Token_stream& ts) {
    double left = term(sym, ts);
    Token t = ts.get();
    while (true) {
        switch (t.kind) {
        case '+':
            left += term(sym, ts);
            t = ts.get();
            break;
        case '-':
            left -= term(sym, ts);
            t = ts.get();
            break;
        default:
            ts.putback(t);
            return left;
        }
    }
}

double Calculator::term(Symbol_table& sym, Token_stream& ts) {
    double left = primary(sym, ts);
    Token t = ts.get();
    while (true) {
        switch (t.kind) {
        case '*':
            left *= primary(sym, ts);
            t = ts.get();
            break;
        case '/':
            left /= primary(sym, ts);
            t = ts.get();
            break;
        case '%':
        {
            double d = primary(sym, ts);
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

double Calculator::primary(Symbol_table& sym, Token_stream& ts) {
    Token t = ts.get();
    switch (t.kind) {
    case numeric:
        return t.val;
    case tname:
    {
        Token t2 = ts.get();
        if (t2.kind != '=') {
            ts.putback(t2);
            return sym.get(t.name);
        }
        double rhs = expression(sym, ts);
        sym.set(t.name, rhs);
        return rhs;
    }
    case '+':
        return primary(sym, ts);
    case '-':
        return -primary(sym, ts);
    case '(':
    {
        double d = expression(sym, ts);
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
        double d = expression(sym, ts);
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
        double d = expression(sym, ts);
        t = ts.get();
        if (t.kind != ',')
            throw std::runtime_error("',' expected");
        int p = narrow<int>(expression(sym, ts));
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
        double val = expression(sym, ts);
        t = ts.get();
        if (t.kind != ')')
            throw std::runtime_error("')' expected");
        int cpy = val;
        if (cpy == val || val >= 0)
            return cpy;
        return cpy - 1;
    }
    default:
        throw std::runtime_error("primary expected");
    }
}

std::string Calculator::usage() {
    return "Supported operations: + - * / % () sqrt() pow() floor()"
        "\nDeclare variables using 'let var = expression'"
        "\nDeclare constants using 'const pi = expression'"
}

double Calculator::operator()(Token_stream ts) {
while (ts) {
    Token t = ts.get();
    while (ts && t.kind == tprint)
        t = ts.get();
    if (!ts)
        return 0;
    switch (t.kind) {
    case tquit:
        return 0;
    default:
        ts.putback(t);
        return statement(sym, ts);
    }
}
return 0;
}
