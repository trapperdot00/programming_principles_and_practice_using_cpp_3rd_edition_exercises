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


## [Exercise 1](exercises/01/01.cpp)
Modify the calculator program from `Chapter 6` to make the input stream an explicit parameter (as shown in §7.4.8), rather than simply using `cin`. Also give the `Token_stream` constructor (§6.8.2) an `istream&` parameter so that when we figure out how to make our own `istream`s (e.g., attached to files), we can use the calculator for those. Hint: Don’t try to copy an `istream`.

## [Exercise 2](exercises/02/01.cpp)
Write a function `print()` that prints a `vector` of `int`s to `cout`. Give it two arguments: a `string` for “labeling” the output and a `vector`.

## [Exercise 3](exercises/03/01.cpp)
Create a `vector` of Fibonacci numbers and print them using the function from exercise 2. To create the `vector`, write a function, `fibonacci(x,y,v,n)`, where integers `x` and `y` are `int`s, `v` is an empty `vector<int>`, and `n` is the number of elements to put into `v`; `v[0]` will be `x` and `v[1]` will be `y`. A Fibonacci number is one that is part of a sequence where each element is the sum of the two previous ones. For example, starting with 1 and 2, we get 1, 2, 3, 5, 8, 13, 21, ... . Your `fibonacci()` function should make such a sequence starting with its x and y arguments.

## [Exercise 4](exercises/04/01.cpp)
An `int` can hold integers only up to a maximum number. Find an approximation of that maximum number by using `fibonacci()`.

## [Exercise 5](exercises/05/01.cpp)
Write two functions that reverse the order of elements in a `vector<int>`. For example, 1, 3, 5, 7, 9 becomes 9, 7, 5, 3, 1. The first reverse function should produce a new `vector` with the reversed sequence, leaving its original `vector` unchanged. The other reverse function should reverse the elements of its `vector` without using any other `vector`s (hint: `swap`).

## [Exercise 6](exercises/06/01.cpp)
Write versions of the functions from exercise 5, but with a `vector<string>`.

## [Exercise 7](exercises/07/01.cpp)
Read five names into a `vector<string>` name, then prompt the user for the ages of the people named and store the ages in a `vector<double> age`. Then print out the five (`name[i],age[i]`) pairs. Sort the names (`sort(name.begin(),name.end())`) and print out the (`name[i],age[i]`) pairs. The tricky part here is to get the `age vector` in the correct order to match the sorted `name vector`. Hint: Before sorting `name`, take a copy and use that to make a copy of `age` in the right order after sorting `name`.

## [Exercise 8](exercises/08/01.cpp)
Do the previous exercise but allow an arbitrary number of names.

## [Exercise 9](exercises/09/01.cpp)
Write a function that given two `vector<double>`s `price` and `weight` computes a value (an “index”) that is the sum of all `price[i]*weight[i]`. Make sure to have `weight.size()==price.size()`.

## [Exercise 10](exercises/10/01.cpp)
Write a function `maxv()` that returns the largest element of a `vector` argument.

## [Exercise 11](exercises/11/01.cpp)
Write a function that finds the smallest and the largest element of a `vector` argument and also computes the mean and the median. Do not use global variables. Either return a `struct` containing the results or pass them back through reference arguments. Which of the two ways of returning several result values do you prefer and why?

## [Exercise 12](exercises/12)
Improve `print_until_s()` from §7.4.2. Test it. What makes a good set of test cases? Give reasons. Then, write a `print_until_ss()` that prints until it sees a second occurrence of its `quit` argument.

## [Exercise 13](exercises/13/01.cpp)
Write a function that takes a `vector<string>` argument and returns a `vector<int>` containing the number of characters in each `string`. Also find the longest and the shortest `string` and the lexicographically first and last `string`. How many separate functions would you use for these tasks? Why?

## [Exercise 14](exercises/14/01.cpp)
Can we declare a non-reference function argument `const` (e.g., `void f(const int);`)? What might that mean? Why might we want to do that? Why don’t people do that often? Try it; write a couple of small programs to see what works.
