# 6: Completing a Program

- [Try This](#try-this-1)
- [Drill](#drill-1)
- [Review](#review-1)
- [Terms](terms.txt)
- [Exercises](#exercise-1)

## Try This 1
Feed a few such “problematic” expressions to the calculator and try to figure out in how many ways you can get it to misbehave. Can you get it to crash, that is, to get it past our error handling and give a machine error? We don’t think you can. Can you get it to exit without a useful error message? You can.


## [Drill 1](drill/01/02.cpp)
Starting from the file `calculator08buggy.cpp`, get the calculator to compile.

## [Drill 2](drill/02/01.cpp)
Go through the entire program and add appropriate comments.

## [Drill 3](drill/03/01.cpp)
As you commented, you found errors (deviously inserted especially for you to find). Fix them; they are not in the text of the book.

## [Drill 4](drill/04/01.txt)
Testing: prepare a set of inputs and use them to test the calculator. Is your list pretty complete? What should you look for? Include negative values, 0, very small, very large, and “silly” inputs.

## [Drill 5](drill/05/01.cpp)
Do the testing and fix any bugs that you missed when you commented.

## [Drill 6](drill/06/01.cpp)
Add a predefined name `k` meaning `1000`.

## [Drill 7](drill/07/01.cpp)
Give the user a square root function `sqrt()`, for example, `sqrt(2+6.7)`. Naturally, the value of `sqrt(x)` is the square root of `x`; for example, `sqrt(9)` is `3`. Use the standard-library `sqrt()` function to implement that calculator `sqrt()`. Remember to update the comments, including the grammar.

## [Drill 8](drill/08/01.cpp)
Catch attempts to take the square root of a negative number and print an appropriate error message.

## [Drill 9](drill/09/01.cpp)
Allow the user to use `pow(x,i)` to mean “Multiply `x` with itself `i` times”; for example, `pow(2.5,3)` is `2.5*2.5*2.5`. Require `i` to be an integer using the technique we used for `%` (§6.5).

## [Drill 10](drill/10/01.cpp)
Change the “declaration keyword” from `let` to `#`.

## [Drill 11](drill/11/01.cpp)
Change the “quit keyword” from `quit` to `exit`. That will involve defining a string for `quit` just as we did for `let` in §6.8.2.


## [Review 1](review/01.txt)
What is the purpose of working on the program after the first version works? Give a list of reasons.

## [Review 2](review/02.txt)
Why does `1+2; q` typed into the calculator not quit after it receives an error?

## [Review 3](review/03.txt)
Why did we choose to make a constant character called `number`?

## [Review 4](review/04.txt)
We split `main()` into two separate functions. What does the new function do and why did we split `main()`?

## [Review 5](review/05.txt)
Why do we split code into multiple functions? State principles.

## [Review 6](review/06.txt)
What is the purpose of commenting?

## [Review 7](review/07.txt)
What is the use of symbolic constants?

## [Review 8](review/08.txt)
Why do we care about code layout?

## [Review 9](review/09.txt)
How do we handle `%` (remainder) of floating-point numbers?

## [Review 10](review/10.txt)
What does `is_declared()` do and how does it work?

## [Review 11](review/11.txt)
The input representation for `let` is more than one character. How is it accepted as a single token in the modified code?

## [Review 12](review/12.txt)
What are the rules for what names can and cannot be in a calculator program?

## [Review 13](review/13.txt)
Why is it a good idea to build a program incrementally?

## [Review 14](review/14.txt)
When do you start to test?

## [Review 15](review/15.txt)
When do you retest?

## [Review 16](review/16.txt)
How do you decide what should be a separate function?

## [Review 17](review/17.txt)
How do you choose names for variables and functions? List possible reasons.

## [Review 18](review/18.txt)
What should be in comments and what should not?

## [Review 19](review/19.txt)
When do we consider a program finished?


## [Exercise 1](exercises/01/01.cpp)
Allow underscores in the calculator’s variable names.

## [Exercise 2](exercises/02/01.cpp)
Provide an assignment operator, `=`, so that you can change the value of a variable after you have introduced it using `let`. Discuss why that can be useful and how it can be a source of problems.

## [Exercise 3](exercises/03/01.cpp)
Provide named constants that you really can’t change the value of. Hint: You have to add a member to `Variable` that distinguishes between constants and variables and check for it in `set_value()`. If you want to let the user define constants (rather than just having `pi` and `e` defined as constants), you’ll have to add a notation to let the user express that, for example, `const pi = 3.14;`.
