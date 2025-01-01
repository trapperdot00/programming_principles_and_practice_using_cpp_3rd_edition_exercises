# 4: Errors!

- [Try This](#try-this-1)
- [Drill](#drill)
- [Review](#review-1)
- [Terms](terms.txt)
- [Exercises](#exercise-1)

## [Try This 1](try_this/01/01.cpp)
Try to compile those examples and see how the compiler responds.

## [Try This 2](try_this/02/01.cpp)
Try to compile those examples and see how the compiler responds. Try thinking of a few more errors yourself and try those.

## [Try This 3](try_this/03)
Test this program with a variety of values. Print out the values of `area1`, `area2`, `area3`, and `ratio`. Insert more tests until all errors are caught. How do you know that you caught all errors? This is not a trick question. In this particular example, you can give a valid argument for having caught all errors.

## [Try This 4](try_this/04/01.cpp)
To see what an uncaught exception error looks like, run a small program that uses `error()` without catching any exceptions.

## [Try This 5](try_this/05/01.txt)
Our hexagon was regular with 2cm sides. Did we get that answer right? Just do the “back of the envelope” calculation. Take a piece a paper and scribble on it. Don’t feel that’s beneath you. Many famous scientists have been greatly admired for their ability to come up with an approximate answer using a pencil and the back of an envelope (or a napkin). This is an ability – a simple habit, really – that can save us a lot of time and confusion.

## [Try This 6](try_this/06/01.txt)
Estimate those driving times. Also, estimate the corresponding flight times (using ordinary commercial air travel). Then, try to verify your estimates by using appropriate sources, such as maps and timetables. We’d use online sources.

## [Try This 7](try_this/07/01.txt)
Find a pair of values so that the precondition of this version of area holds, but the postcondition doesn’t.

## Drill
Below are 25 code fragments. Each is meant to be inserted into this “scaffolding”:
```
#include "PPP.h"

int main()
try{
    <<your code here>>
    return 0;
}
catch (exception& e){
    cerr << "error: " << e.what() << '\n';
    return 1;
}
catch (...) {
    cerr << "Oops: unknown exception!\n";
    return 2;
}
```
Each has zero or more errors. Your task is to find and remove all errors ineach program. When you have removed those bugs, the resulting programwill compile, run, and write “Success!” Even if you think you have spotted an error, you still need to enter the (original, unimproved) program fragment and test it; you may have guessed wrong about what the error is, or there may be more errors in a fragment than you spotted. Also, one purpose of this drill is to give you a feel for how your compiler reacts to different kinds of errors. Do not enter the scaffolding 25 times – that’s a job for cut and paste or some similar “mechanical” technique. Do not fix problems by simply deleting a statement; repair them by changing, adding, or deleting a few characters.

## [Drill 1](drill/01/01.cpp)
`Cout << "Success!\n";`

## [Drill 2](drill/02/01.cpp)
`cout << "Success!\n;`

## [Drill 3](drill/03/01.cpp)
`cout << "Success" << !\n"`

## [Drill 4](drill/04/01.cpp)
`cout << success << ’\n’;`

## [Drill 5](drill/05/01.cpp)
`string res = 7; vector<int> v(10); v[5] = res; cout << "Success!\n";`

## [Drill 6](drill/06/01.cpp)
`vector<int> v(10); v(5) = 7; if (v(5)!=7) cout << "Success!\n";`

## [Drill 7](drill/07/01.cpp)
`if (cond) cout << "Success!\n"; else cout << "Fail!\n";`

## [Drill 8](drill/08/01.cpp)
`bool c = false; if (c) cout << "Success!\n"; else cout << "Fail!\n";`

## [Drill 9](drill/09/01.cpp)
`string s = "ape"; boo c = "fool"<s; if (c) cout << "Success!\n";`

## [Drill 10](drill/10/01.cpp)
`string s = "ape"; if (s=="fool") cout << "Success!\n";`

## [Drill 11](drill/11/01.cpp)
`string s = "ape"; if (s=="fool") cout < "Success!\n";`

## [Drill 12](drill/12/01.cpp)
`string s = "ape"; if (s+"fool") cout < "Success!\n";`

## [Drill 13](drill/13/01.cpp)
`vector<char> v(5); for (int i = 0; 0<v.size(); ++i) ; cout << "Success!\n";`

## [Drill 14](drill/14/01.cpp)
`vector<char> v(5); for (int i = 0; i<=v.size(); ++i) ; cout << "Success!\n";`

## [Drill 15](drill/15/01.cpp)
`string s = "Success!\n"; for (int i = 0; i<6; ++i) cout << s[i];`

## [Drill 16](drill/16/01.cpp)
`if (true) then cout << "Success!\n"; else cout << "Fail!\n";`

## [Drill 17](drill/17/01.cpp)
`int x = 2000; char c = x; if (c==2000) cout << "Success!\n";`

## [Drill 18](drill/18/01.cpp)
`string s = "Success!\n"; for (int i = 0; i<10; ++i) cout << s[i];`

## [Drill 19](drill/19/01.cpp)
`vector v(5); for (int i = 0; i<=v.size(); ++i) ; cout << "Success!\n";`

## [Drill 20](drill/20/01.cpp)
`int i = 0; int j = 9; while (i<10) ++j; if (j<i) cout << "Success!\n";`

## [Drill 21](drill/21/01.cpp)
`int x = 2; double d = 5/(x−2); if (d==2*x+0.5) cout << "Success!\n";`

## [Drill 22](drill/22/01.cpp)
`string<char> s = "Success!\n"; for (int i = 0; i<=10; ++i) cout << s[i];`

## [Drill 23](drill/23/01.cpp)
`int i = 0; while (i<10) ++j; if (j<i) cout << "Success!\n";`

## [Drill 24](drill/24/01.cpp)
`int x = 4; double d = 5/(x−2); if (d=2*x+0.5) cout << "Success!\n";`

## [Drill 25](drill/25/01.cpp)
`cin << "Success!\n";`


## [Review 1](review/01.txt)
Name four major types of errors and briefly define each one.

## [Review 2](review/02.txt)
What kinds of errors can we ignore in student programs?

## [Review 3](review/03.txt)
What guarantees should every completed project offer?

## [Review 4](review/04.txt)
List three approaches we can take to eliminate errors in programs and produce acceptable software.

## [Review 5](review/05.txt)
Why do we hate debugging?

## [Review 6](review/06.txt)
What is a syntax error? Give five examples.

## [Review 7](review/07.txt)
What is a type error? Give five examples.

## [Review 8](review/08.txt)
What is a linker error? Give three examples.

## [Review 9](review/09.txt)
What is a logic error? Give three examples.

## [Review 10](review/10.txt)
List four potential sources of program errors discussed in the text.

## [Review 11](review/11.txt)
How do you know if a result is plausible? What techniques do you have to answer such questions?

## [Review 12](review/12.txt)
How do you test if an input operation succeeded?

## [Review 13](review/13.txt)
Compare and contrast having the caller of a function handle a run-time error vs. having the called function handle the run-time error.

## [Review 14](review/14.txt)
When is throwing an exception preferable to returning an “error value”?

## [Review 15](review/15.txt)
When is returning an “error value” preferable to throwing an exception?

## [Review 16](review/16.txt)
Describe the process of how exceptions are thrown and caught.

## [Review 17](review/17.txt)
Why, with a `vector` called `v`, is `v[v.size()]` a range error? What would be the result of calling this?

## [Review 18](review/18.txt)
What is an assertion?

## [Review 19](review/19.txt)
Define precondition and postcondition; give an example (that is not the `area()` function from this chapter), preferably a computation that requires a loop.

## [Review 20](review/20.txt)
When would you not test a precondition?

## [Review 21](review/21.txt)
When would you not test a postcondition?

## [Review 22](review/22.txt)
What are the steps in debugging a program?

## [Review 23](review/23.txt)
Why does commenting help when debugging?

## [Review 24](review/24.txt)
How does testing differ from debugging?

## [Review 25](review/25.txt)
What is a random number?

## [Review 26](review/26.txt)
How do we use `random_int()` and `seed()`?


## Exercise 1
If you haven’t already, do the `TRY THIS` exercises from this chapter.

## [Exercise 2](exercises/02/01.cpp)
The following program takes in a temperature value in Celsius and converts it to Kelvin. This code has many errors in it. Find the errors, list them, and correct the code.
```
double ctok(double c)   // converts Celsius to Kelvin
{
    int k = c + 273.25;
    return int
}

int main()
{
    double c = 0;   // declare input variable
    cin >> d;   // retrieve temperature to input variable
    double k = ctok("c");   // convert temperature
    Cout << k << '/n' ; // print out temperature
}
```

## [Exercise 3](exercises/03/01.cpp)
Absolute zero is the lowest temperature that can be reached; it is -273.15C, or 0K. The above program, even when corrected, will produce erroneous results when given a temperature below this. Place a check in the main program that will produce an error if a temperature is given below -273.15C.

## [Exercise 4](exercises/04/01.cpp)
Do `exercise 3` again, but this time handle the error inside `ctok()`.

## [Exercise 5](exercises/05/01.cpp)
Add to the program so that it can also convert from Kelvin to Celsius.

## [Exercise 6](exercises/06/01.cpp)
Write a program that converts from Celsius to Fahrenheit and from Fahrenheit to Celsius. Use estimation (§4.7.1) to see if your results are plausible.

## [Exercise 7](exercises/07/01.cpp)
Quadratic equations are of the form a*x2 + b*x + c = 0. To solve these, one uses the quadratic formula, There is a problem, though: if b^2- 4ac is less than zero, then it will fail. Write a program that can calculate x for a quadratic equation. Create a function that prints out the roots of a quadratic equation, given a, b, c. When the program detects an equation with no real roots, have it print out a message. How do you know that your results are plausible? Can you check that they are correct?

## [Exercise 8](exercises/08/01.cpp)
Write a program that reads and stores a series of integers and then computes the sum of the first N integers. First ask for N, then read the values into a `vector`, then calculate the sum of the first N values. For example:
```
Please enter the number of values you want to sum: 3
Please enter some integers (press ’|’ to stop): 12 23 13 24 15 |
The sum of the first 3 numbers ( 12 23 13 ) is 48
```
Handle all inputs. For example, make sure to give an error message if the user asks for a sum of more numbers than there are in the vector.

## [Exercise 9](exercises/09/01.cpp)
Modify the program from the previous exercise to write out an error if the result cannot be represented as an `int`.

## [Exercise 10](exercises/10/01.cpp)
Modify the program from the previous exercise to use `double` instead of `int`. Also, make a `vector` of doubles containing the N-1 differences between adjacent values and write out that `vector` of differences.

## [Exercise 11](exercises/11/01.cpp)
Write a program that writes out the first N values of the Fibonacci series, that is, the series that starts with 1 1 2 3 5 8 13 21 34. The next number of the series is the sum of the two previous ones. Find the largest Fibonacci number that fits in an `int`.

## [Exercise 12](exercises/12/01.cpp)
Implement a little guessing game called (for some obscure reason) “Bulls and Cows.” The program has a `vector` of four different integers in the range 0 to 9 (e.g., 1234 but not 1122) and it is the user’s task to discover those numbers by repeated guesses. Say the number to be guessed is 1234 and the user guesses 1359; the response should be “1 bull and 1 cow” because the user got one digit (1) right and in the right position (a bull) and one digit (3) right but in the wrong position (a cow). The guessing continues until the user gets four bulls, that is, has the four digits correct and in the correct order.

## [Exercise 13](exercises/13/01.cpp)
The program is a bit tedious because the answer is hard-coded into the program. Make a version where the user can play repeatedly (without stopping and restarting the program) and each game has a new set of four digits. You can get four random digits by calling the random number generator `random_int(0,9)` from `PPP_support` (and §4.7.5) four times. You will note that if you run that program repeatedly, it will pick the same sequence of four digits each time you start the program. To avoid that, ask the user to enter a number (any number) and call `seed(n)`, also from `PPP_support`, where n is the number the user entered before calling `random_int(0,10)`. Such an n is called a seed, and different seeds give different sequences of random numbers.

## [Exercise 14](exercises/14/01.cpp)
Read (day-of-the-week,value) pairs from standard input. For example:
```
Tuesday 23 Friday 56 Tuesday −3 Thursday 99
```
Collect all the values for each day of the week in a `vector<int>`. Write out the values of the seven day-of-the-week `vector`s. Print out the sum of the values in each `vector`. Ignore illegal days of the week, such as `Funday`, but accept common synonyms such as `Mon` and `monday`. Write out the number of rejected values.
