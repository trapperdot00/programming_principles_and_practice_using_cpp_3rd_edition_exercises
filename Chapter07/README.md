# 6: Completing a Program

- [Try This](#try-this-1)
- [Drill](#drill-1)
- [Review](#review-1)
- [Terms](terms.txt)
- [Exercises](#exercise-1)

## [Try This 1](try_this/01)
Compile the three examples above to see how the compiler complains. Then add a definition of `f()` to get a running version.

## [Try This 2](try_this/02/01.cpp)
Type in the example above and indent it properly. What suspicious constructs and bugs can you now find?

## [Try This 3](try_this/03/01.cpp)
Try examples like the ones above converting all combinations of an `int`, a `double`, and a `char`. Use values `1001`, `7.7`, and `'x'`. Try with implicit conversion and `narrow`. Write out the results for the cases where the program compiles. What errors and warnings did you get?


## [Drill 1](drill/01/01.cpp)
Write three functions `swap_v(int,int)`, `swap_r(int&,int&)`, and `swap_cr(const int&, const int&)`. Each should have the body
```
{ int temp; temp = a, a=b; b=temp; }
```
where `a`and `b` are the names of the arguments.

Try calling each swap like this
```
int x = 7;
int y = 9;
swap_?(x,y);        // replace ? by v, r, or cr
swap_?(7,9);
const int cx = 7;
const int cy = 9;
swap_?(cx,cy);
swap_?(7.7,9.9);
double dx = 7.7;
double dy = 9.9;
swap_?(dx,dy);
swap_?(7.7,9.9);
```
Which functions and calls compiled, and why? After each swap that compiled, print the value of the arguments after the call to see if they were actually swapped. If you are surprised by a result, consult §7.5.

## [Drill 2](drill/02/01.cpp)
Write a program using a single file containing three namespaces `X`, `Y`, and `Z` so that the following `main()` works correctly:
```
int main()
{
    X::var = 7;
    X::print();         // print X's var
    using namespace Y;
    var = 9;
    print();            // print Y's var
    {
        using Z::var;
        using Z::print;
        var = 11;
        print();        // print Z's var
    }
    print();            // print Y's var
    X::print(); // print X's var
```
Each namespace needs to define a variable called `var` and a function called `print()` that outputs the appropriate `var` using `cout`.

## Drill 3
Create a module `foo` with the suffix appropriate to your system:
```
int foo = 0;
export void print_foo() { ... };
export void set_foo(int x} { foo = x; }
export int get_foo() { return x; }
```
Add what it takes to get the `...` part to print `foo`. Write file `use.cpp` that `import`s `foo` and tests it. Get the resulting program to compile and run.

## [Drill 4](drill/04)
Create a header file: `foo.h`:
```
extern int foo;
void print_foo();
void print(int);
```
Write a file `foo.cpp` that implements the functions declared in `foo.h`. Write file `use.cpp` that `#include`s `foo.h` and tests it. Get the resulting program to compile and run.
