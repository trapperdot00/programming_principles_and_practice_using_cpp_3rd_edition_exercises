# 5: Writing a Program

- [Try This](#try-this-1)
- [Drill](#drill-1)
- [Review](#review-1)
- [Terms](terms.txt)
- [Exercises](#exercise-1)

## Try This 1
On the other hand, why shouldn’t we be able to find a simple solution to this problem? It doesn’t seem to be all that difficult. If nothing else, trying would give us a better appreciation of the problem and the eventual solution. Consider what you might do right away. For example, look at the input `12.5+2`. We could tokenize that, decide that the expression was simple, and compute the answer. That may be a bit messy, but straightforward, so maybe we could proceed in this direction and find something that’s good enough! Consider what to do if we found both a `+` and a `*` in the line `2+3*4`. That too can be handled by “brute force.” How would we deal with a complicated expression, such as `1+2*3/4%5+(6−7*(8))`? And how would we deal with errors, such as `2+*3` and `2&3`? Consider this for a while, maybe doodling a bit on a piece of paper trying to outline possible solutions and interesting or important input expressions.

## [Try This 2](try_this/02/01.cpp)
This first version of the calculator program (including get_token()) is available as file `calculator00.cpp`. Get it to run and try it out.

## [Try This 3](try_this/03/01.cpp)
Get the calculator as presented above to run, see what it does, and try to figure out why it works as it does.

## [Drill 1](drill/01/02.cpp)
Take the calculator from the file `calculator02buggy.cpp`. Get it to compile. You need to find and fix a few bugs. Those bugs are not in the text in the book. Find the three logic errors deviously inserted in `calculator02buggy.cpp` and remove them so that the calculator produces correct results.

## [Drill 2](drill/02/01.cpp)
Change the character used as the exit command from `q` to `x`.

## [Drill 3](drill/03/01.cpp)
Change the character used as the print command from `;` to `=`.

## [Drill 4](drill/04/01.cpp)
Add a greeting line in `main()`:
```
"Welcome to our simple calculator.
Please enter expressions using floating−point numbers."
```

## [Drill 5](drill/05/01.cpp)
Improve that greeting by mentioning which operators are available and how to print and exit.


## [Review 1](review/01.txt)
What do we mean by “Programming is understanding”?

## [Review 2](review/02.txt)
The chapter details the creation of a calculator program. Write a short analysis of what the calculator should be able to do.

## [Review 3](review/03.txt)
How do you break a problem up into smaller manageable parts?

## [Review 4](review/04.txt)
Why is creating a small, limited version of a program a good idea?

## [Review 5](review/05.txt)
Why is feature creep a bad idea?

## [Review 6](review/06.txt)
What are the three main phases of software development?

## [Review 7](review/07.txt)
What is a “use case”?

## [Review 8](review/08.txt)
What is the purpose of testing?

## [Review 9](review/09.txt)
According to the outline in the chapter, describe the difference between a `Term`, an `Expression`, a `Number`, and a `Primary`.

## [Review 10](review/10.txt)
In the chapter, an input was broken down into its components: `Term`s, `Expression`s, `Primary`s, and `Number`s. Do this for `(17+4)/(5−1)`.

## [Review 11](review/11.txt)
Why does the program not have a function called `number()`?

## [Review 12](review/12.txt)
What is a token?

## [Review 13](review/13.txt)
What is a grammar? A grammar rule?

## [Review 14](review/14.txt)
What is a class? What do we use classes for?

## [Review 15](review/15.txt)
How can we provide a default value for a member of a class?

## [Review 16](review/16.txt)
In the expression function, why is the default for the `switch`-statement to “put back” the token?

## [Review 17](review/17.txt)
What is “look-ahead”?

## [Review 18](review/18.txt)
What does `putback()` do and why is it useful?

## [Review 19](review/19.txt)
Why is the remainder (modulus) operation, `%`, difficult to implement in the `term()`?

## [Review 20](review/20.txt)
What do we use the two data members of the `Token` class for?

## [Review 21](review/21.txt)
Why do we (sometimes) split a class’s members into `private` and `public` members?

## [Review 22](review/22.txt)
What happens in the `Token_stream` class when there is a token in the buffer and the `get()` function is called?

## [Review 23](review/23.txt)
Why were the `';'` and `'q'` characters added to the `switch`-statement in the `get()` function of the `Token_stream` class?

## [Review 24](review/24.txt)
When should we start testing our program?

## [Review 25](review/25.txt)
What is a “user-defined type”? Why would we want one?

## [Review 26](review/26.txt)
What is the interface to a C++ “user-defined type”?

## [Review 27](review/27.txt)
Why do we want to rely on libraries of code?


## Exercise 1
If you haven’t already, do the TRY THIS exercises from this chapter.

## [Exercise 2](exercises/02/01.cpp)
Add the ability to use `{}` as well as `()` in the program, so that `{(4+5)*6} / (3+4)` will be a valid expression.

## [Exercise 3](exercises/03/01.cpp)
Add a factorial operator: use a suffix `!` operator to represent “factorial.” For example, the expression `7!` means `7 * 6 * 5 * 4 * 3 * 2 * 1`. Make `!` bind tighter than `*` and `/`; that is, `7*8!` means `7*(8!)` rather than `(7*8)!`. Begin by modifying the grammar to account for a higher-level operator. To agree with the standard mathematical definition of factorial, let `0!` evaluate to `1`. Hint: The calculator functions deal with `double`s, but factorial is defined only for `int`s, so just for `x!`, assign the `x` to an `int` and calculate the factorial of that `int`.

## [Exercise 4](exercises/04/01.cpp)
Define a class `Name_value` that holds a string and a value. Rework exercise 20 in Chapter 3 to use a `vector<Name_value>` instead of two `vectors`.

## [Exercise 5](exercises/05/01.cpp)
Write a grammar for bitwise logical expressions. A bitwise logical expression is much like an arithmetic expression except that the operators are `!` (not), `˜` (complement), `&` (and), `|` (or), and `ˆ` (exclusive or). Each operator does its operation to each bit of its integer operands (see PPP2.§25.5). `!` and `˜` are prefix unary operators. A `ˆ` binds tighter than a `|` (just as `*` binds tighter than `+`) so that `x|yˆz` means `x|(yˆz)` rather than `(x|y)ˆz`. The `&` operator binds tighter than `ˆ` so that `xˆy&z` means `xˆ(y&z)`.

## [Exercise 6](exercises/06/01.cpp)
Redo the “Bulls and Cows” game from exercise 12 in Chapter 4 to use four letters rather than four digits.

## [Exercise 7](exercises/07/01.cpp)
Write a program that reads digits and composes them into integers. For
example, `123` is read as the characters 1, 2, and 3. The program should
output `123 is 1 hundred and 2 tens and 3 ones`. The number should be output
as an `int` value. Handle numbers with one, two, three, or four digits.
Hint: To get the integer value `5` from the character `'5'` subtract `'0'`, that is,
`'5'−'0'==5`.

## [Exercise 8](exercises/08/01.cpp)
A permutation is an ordered subset of a set. For example, say you wanted to pick a combination to a vault. There are 60 possible numbers, and you need three different numbers for the combination. There are `P(60, 3)` permutations for the combination, where `P` is defined by the formula `P(a, b) = (a!) / ((a - b)!)` where `!` is used as a suffix factorial operator. For example, `4!` is `4*3*2*1`.

Combinations are similar to permutations, except that the order of the objects doesn’t matter. For example, if you were making a “banana split” sundae and wished to use three different flavors of ice cream out of five that you had, you probably wouldn’t care if you put a scoop of vanilla at the beginning or the end or the serving dish. The formula for combinations is `C(a, b) = (P(a, b)) / (b!)`

Design a program that asks users for two numbers, asks them whether they want to calculate permutations or combinations, and prints out the result. This will have several parts. Do an analysis of the above requirements. Write exactly what the program will have to do. Then, go into the design phase. Write pseudo code for the program and break it into subcomponents. This program should have error checking. Make sure that all erroneous inputs will generate good error messages.
