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
