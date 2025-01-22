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


## [Review 1](review/01.txt)
What is the difference between a declaration and a definition?

## [Review 2](review/02.txt)
How do we syntactically distinguish between a function declaration and a function definition?

## [Review 3](review/03.txt)
How do we syntactically distinguish between a variable declaration and a variable definition?

## [Review 4](review/04.txt)
Why can’t you use the functions in the calculator program from `Chapter 5` without declaring one or more of them first?

## [Review 5](review/05.txt)
Is `int a;` a definition or just a declaration?

## [Review 6](review/06.txt)
Why is it a good idea to initialize variables as they are declared?

## [Review 7](review/07.txt)
What can a function declaration consist of?

## [Review 8](review/08.txt)
What is the suffix return type notation, and why might you use it?

## [Review 9](review/09.txt)
What good does indentation do?

## [Review 10](review/10.txt)
What is the scope of a declaration?

## [Review 11](review/11.txt)
What kinds of scope are there? Give an example of each.

## [Review 12](review/12.txt)
What is the difference between a class scope and local scope?

## [Review 13](review/13.txt)
Why should a programmer minimize the number of global variables?

## [Review 14](review/14.txt)
What is the difference between pass-by-value and pass-by-reference?

## [Review 15](review/15.txt)
What is the difference between pass-by-reference and pass-by-const-reference?

## [Review 16](review/16.txt)
What is a `swap()`?

## [Review 17](review/17.txt)
Would you ever define a function with a `vector<double>` as a by-value parameter?

## [Review 18](review/18.txt)
Give an example of undefined order of evaluation. Why can undefined order of evaluation be a problem?

## [Review 19](review/19.txt)
What do `x&&y` and `x||y`, respectively, mean?

## [Review 20](review/20.txt)
Which of the following is standard-conforming C++: functions within functions, functions within classes, classes within classes, classes within functions?

## [Review 21](review/21.txt)
What goes into an activation record?

## [Review 22](review/22.txt)
What is a call stack and why do we need one?

## [Review 23](review/23.txt)
What is the purpose of a namespace?

## [Review 24](review/24.txt)
How does a namespace differ from a class?

## [Review 25](review/25.txt)
What is a `using` declaration?

## [Review 26](review/26.txt)
Why should you avoid `using` directives in a header?

## [Review 27](review/27.txt)
What is namespace `std`?
