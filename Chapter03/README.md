# 3: Computation

- [Try This](#try-this-1)
- [Drill](#drill-1)
- [Review](#review-1)
- [Terms](terms.txt)
- [Exercises](#exercise-1)

## [Try This 1](try_this/01/01.cpp)
Use the example above as a model for a program that converts yen (`'y'`), kroner (`'k'`), and pounds (`'p'`) into dollars. If you like realism, you can find conversion rates on the Web.

## [Try This 2](try_this/02/01.cpp)
Rewrite your currency converter program from the previous `TRY THIS` to use a `switch`-statement. Add a conversion from Swiss francs. Which version of the program is easier to write, understand, and modify? Why?

## [Try This 3](try_this/03/01.cpp)
The character `'b'` is `char(’a’+1)`, `'c'` is `char(’a’+2)`, etc. Use a loop to write out a table of characters with their corresponding integer values:
```
a   97
b   98
 ...
z   122
```

## [Try This 4](try_this/04)
Rewrite the character value example from the previous `TRY THIS` to use a `for`-statement. Then modify your program to also write out a table of the integer values for uppercase letters and digits.

## [Try This 5](try_this/05/01.cpp)
Implement `square()` without using the multiplication operator; that is, do the `x*x` by repeated addition (start a variable result at `0` and add `x` to it `x` times). Then run some version of “the first program” using that `square()`.

## [Try This 6](try_this/06)
Write a program that “bleeps” out words that you don’t like; that is, you read in words using `cin` and print them again on `cout`. If a word is among a few you have defined, you write out `BLEEP` instead of that word. Start with one “disliked word” such as
```
string disliked = "Broccoli";
```
When that works, add a few more.


## [Drill 1](drill/01/01.cpp)
Write a program that consists of a `while`-loop that (each time around the loop) reads in two `int`s and then prints them. Exit the program when a terminating `'|'` is entered.

## [Drill 2](drill/02/01.cpp)
Change the program to write out `the smaller value is:` followed by the smaller of the numbers and `the larger value is:` followed by the larger value.

## [Drill 3](drill/03/01.cpp)
Augment the program so that it writes the line `the numbers are equal` (only) if they are equal.

## [Drill 4](drill/04/01.cpp)
Change the program so that it uses `double`s instead of `int`s.

## [Drill 5](drill/05/01.cpp)
Change the program so that it writes out `the numbers are almost equal` after writing out which is the larger and the smaller if the two numbers differ by less than 1.0/100.

## [Drill 6](drill/06/01.cpp)
Now change the body of the loop so that it reads just one `double` each time around. Define two variables to keep track of which is the smallest and which is the largest value you have seen so far. Each time through the loop write out the value entered. If it’s the smallest so far, write `the smallest so far` after the number. If it is the largest so far, write `the largest so far` after the number.

## [Drill 7](drill/07/01.cpp)
Add a unit to each `double` entered; that is, enter values such as `10cm`, `2.5in`, `5ft`, or `3.33m`. Accept the four units: `cm`, `m`, `in`, `ft`. Assume conversion factors `1m==100cm`, `1in==2.54cm`, `1ft==12in`. Read the unit indicator into a `string`. You may consider `12 m` (with a space between the number and the unit) equivalent to `12m` (without a space).

## [Drill 8](drill/08/01.cpp)
Reject values without units or with “illegal” representations of units, such as `y`, `yard`, `meter`, `km`, and `gallons`.

## [Drill 9](drill/09/01.cpp)
Keep track of the sum of values entered (as well as the smallest and the largest) and the number of values entered. When the loop ends, print the smallest, the largest, the number of values, and the sum of values. Note that to keep the sum, you have to decide on a unit to use for that sum; use meters.

## [Drill 10](drill/10/01.cpp)
Keep all the values entered (converted into meters) in a `vector`. At the end, write out those values.

## [Drill 11](drill/11/01.cpp)
Before writing out the values from the `vector`, sort them (that’ll make them come out in increasing order).


## [Review 1](review/01.txt)
What is a computation?

## [Review 2](review/02.txt)
What do we mean by inputs and outputs to a computation? Give examples.

## [Review 3](review/03.txt)
What are the three requirements a programmer should keep in mind when expressing computations?

## [Review 4](review/04.txt)
What does an expression do?

## [Review 5](review/05.txt)
What is the difference between a statement and an expression, as described in this chapter?

## [Review 6](review/06.txt)
What is an lvalue? List the operators that require an lvalue. Why do these operators, and not the others, require an lvalue?

## [Review 7](review/07.txt)
What is a constant expression?

## [Review 8](review/08.txt)
What is a literal?

## [Review 9](review/09.txt)
What is a symbolic constant and why do we use them?

## [Review 10](review/10.txt)
What is a magic constant? Give examples.

## [Review 11](review/11.txt)
What are some operators that we can use for integers and floating-point values?

## [Review 12](review/12.txt)
What operators can be used on integers but not on floating-point numbers?

## [Review 13](review/13.txt)
What are some operators that can be used for `string`s?

## [Review 14](review/14.txt)
When would a programmer prefer a `switch`-statement to an `if`-statement?

## [Review 15](review/15.txt)
What are some common problems with `switch`-statements?

## [Review 16](review/16.txt)
What is the function of each part of the header line in a `for`-loop, and in what sequence are they executed?

## [Review 17](review/17.txt)
When should the `for`-loop be used and when should the `while`-loop be used?

## [Review 18](review/18.txt)
Describe what the line `char foo(int x)` means in a function definition.

## [Review 19](review/19.txt)
When should you define a separate function for part of a program? List reasons.

## [Review 20](review/20.txt)
What can you do to an `int` that you cannot do to a `string`?

## [Review 21](review/21.txt)
What can you do to a `string` that you cannot do to an `int`?

## [Review 22](review/22.txt)
What is the index of the third element of a `vector`?

## [Review 23](review/23.txt)
How do you write a `for`-loop that prints every element of a `vector`?

## [Review 24](review/24.txt)
What does `vector<char> alphabet(26);` do?

## [Review 25](review/25.txt)
Describe what `push_back()` does to a `vector`.

## [Review 26](review/26.txt)
What does `vector`’s member `size()` do?

## [Review 27](review/27.txt)
What makes `vector` so popular/useful?

## [Review 28](review/28.txt)
How do you sort the elements of a `vector`?


## Exercise 1
If you haven’t already, do the `TRY THIS` exercises from this chapter.

## [Exercise 2](exercises/02/01.cpp)
Write a program that reads a string from input and then, for each character read, prints out the character and its integer value on a line.

## [Exercise 3](exercises/03/01.cpp)
If we define the median of a sequence as “a number so that exactly as many elements come before it in the sequence as come after it,” fix the program in §3.6.3 so that it always prints out a median. Hint: A median need not be an element of the sequence.

## [Exercise 4](exercises/04/01.cpp)
Read a sequence of `double` values into a `vector`. Think of each value as the distance between two cities along a given route. Compute and print the total distance (the sum of all distances). Find and print the smallest and greatest distance between two neighboring cities. Find and print the mean distance between two neighboring cities.

## [Exercise 5](exercises/05/01.cpp)
Write a program to play a numbers guessing game. The user thinks of a number between 1 and 100 and your program asks questions to figure out what the number is (e.g., “Is the number you are thinking of less than 50?”). Your program should be able to identify the number after asking no more than seven questions.

## [Exercise 6](exercises/06/01.cpp)
Write a program that performs as a very simple calculator. Your calculator should be able to handle the four basic math operations – add, subtract, multiply, and divide – on two input values. Your program should prompt the user to enter three arguments: two `double` values and a character to represent an operation. If the entry arguments are `35.6, 24.1`, and `'+'`, the program output should be `The sum of 35.6 and 24.1 is 59.7`. In `Chapter 5` and `Chapter 6`, we look at a much more sophisticated simple calculator.

## [Exercise 7](exercises/07)
Make a `vector` holding the ten `string` values `"zero"`, `"one"`, . . . `"nine"`. Use that in a program that converts a digit to its corresponding spelled-out value; e.g., the input `7` gives the output `seven`. Have the same program, using the same input loop, convert spelled-out numbers into their digit form; e.g., the input `seven` gives the output `7`.

## [Exercise 8](exercises/08/01.cpp)
Modify the “mini calculator” from `exercise 6` to accept (just) single-digit numbers written as either digits or spelled out.

## [Exercise 9](exercises/09/01.cpp)
There is an old story that the emperor wanted to thank the inventor of the game of chess and asked the inventor to name his reward. The inventorasked for one grain of rice for the first square, 2 for the second, 4 for the third, and so on, doubling for each of the 64 squares. That may sound modest, but there wasn’t that much rice in the empire! Write a program to calculate how many squares are required to give the inventor at least 1000 grains of rice, at least 1,000,000 grains, and at least 1,000,000,000 grains. You’ll need a loop, of course, and probably an `int` to keep track of which square you are at, an `int` to keep the number of grains on the current square, and an `int` to keep track of the grains on all previous squares. We suggest that you write out the value of all your variables for each iteration of the loop so that you can see what’s going on.

## [Exercise 10](exercises/10)
Try to calculate the number of rice grains that the inventor asked for in
`exercise 9` above. You’ll find that the number is so large that it won’t fit
in an `int` or a `double`. Observe what happens when the number gets too
large to represent exactly as an `int` and as a `double`. What is the largest
number of squares for which you can calculate the exact number of
grains (using an `int`)? What is the largest number of squares for which
you can calculate the approximate number of grains (using a `double`)?

## [Exercise 11](exercises/11/01.cpp)
Write a program that plays the game “Rock, Paper, Scissors.” If you are not familiar with the game do some research (e.g., on the Web using Google). Research is a common task for programmers. Use a `switch`- statement to solve this exercise. Also, the machine should give random answers (i.e., select the next rock, paper, or scissors randomly). Real randomness is too hard to provide just now, so just build a `vector` with a sequence of values to be used as “the next value.” If you build the `vector` into the program, it will always play the same game, so maybe you should let the user enter some values. Try variations to make it less easy for the user to guess which move the machine will make next.

## [Exercise 12](exercises/12/01.cpp)
Create a program to find all the prime numbers between 1 and 100. One way to do this is to write a function that will check if a number is prime (i.e., see if the number can be divided by a prime number smaller than itself) using a `vector` of primes in order (so that if the `vector` is called `primes`, `primes[0]==2`, `primes[1]==3`, `primes[2]==5`, etc.). Then write a loop that goes from 1 to 100, checks each number to see if it is a prime, and stores each prime found in a `vector`. Write another loop that lists the primes you found. You might check your result by comparing your `vector` of prime numbers with primes. Consider 2 the first prime.

## [Exercise 13](exercises/13/01.cpp)
Create a program to find all the prime numbers between 1 and 100. There is a classic method for doing this, called the “Sieve of Eratosthenes.” If you don’t know that method, get on the Web and look it up. Write your program using this method.

## [Exercise 14](exercises/14/01.cpp)
Write a program that takes an input value `n` and then finds the first n primes.

## [Exercise 15](exercises/15/01.cpp)
In the drill, you wrote a program that, given a series of numbers, found the max and min of that series. The number that appears the most times in a sequence is called the mode. Create a program that finds the mode of a set of positive integers.

## [Exercise 16](exercises/16/01.cpp)
Write a program that finds the min, max, and mode of a sequence of `string`s.

## [Exercise 17](exercises/17/01.cpp)
Write a program to solve quadratic equations. A quadratic equation is of the form `ax2 + bx + c = 0`. If you don’t know the formula for solving such an expression, do some research. Remember, researching how to solve a problem is often necessary before a programmer can teach the computer how to solve it. Use `double`s for the user inputs for `a`, `b`, and `c`. Since there are two solutions to a quadratic equation, output both `x1` and `x2`.

## [Exercise 18](exercises/18/01.cpp)
Write a program where you first enter a set of name-and-value pairs, such as `Joe 17` and `Barbara 22`. For each pair, add the name to a `vector` called `names` and the number to a `vector` called `scores` (in corresponding positions, so that if `names[7]=="Joe"` then `scores[7]==17`). Terminate input with `NoName 0`. Check that each name is unique and terminate with an error message if a name is entered twice. Write out all the (name,score) pairs, one per line.

## [Exercise 19](exercises/19/01.cpp)
Modify the program from the previous exercise so that once you have entered the name-and-value pairs, you ask for values: In a loop, when you enter a name, the program will output the corresponding score or `name not found`.

## [Exercise 20](exercises/20/01.cpp)
Modify the program from the previous exercise so that once you have entered the name-and-value pairs, you ask for names: In a loop, when you enter a value, the program will output all the names with that score or `score not found`.
