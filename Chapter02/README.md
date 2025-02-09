# 2: Objects, Types, and Values

- [Try This](#try-this-1)
- [Drill](#drill-1)
- [Review](#review-1)
- [Terms](terms.txt)
- [Exercises](#exercise-1)

## [Try This 1](try_this/01)
Get the “name and age” example to run. Then, modify it to write out the age in number of months: read the input in years and multiply (using the * operator) by 12. Read the age into a `double` to allow for children who can be very proud of being five and a half years old rather than just five.

## [Try This 2](try_this/02)
Get this little program to run. Then, modify it to read an `int` rather than a `double`. Also, “exercise” some other operations, such as the modulo operator, `%`. Note that for `int`s `/` is integer division and `%` is remainder (modulo), so that `5/2` is `2` (and not `2.5` or `3`) and `5%2` is `1`. The definitions of integer `*`, `/`, and `%` guarantee that for two positive `int`s `a` and `b` we have `a/b * b + a%b == a`.

## Try This 3
Execute this program yourself using a piece of paper. Use the input The cat cat jumped. Even experienced programmers use this technique to visualize the actions of small sections of code that somehow don’t seem completely obvious.

## [Try This 4](try_this/04/01.cpp)
Get the “repeated word detection program” to run. Test it with the sentence `She she laughed "he he he!" because what he did did not look very very good good`. How many repeated words were there? Why? What is the definition of word used here? What is the definition of repeated word? (For example, is `She she` a repetition?)

## [Try This 5](try_this/05)
Compile the “Goodbye, cruel world!” program and examine the error messages. Did the compiler find all the errors? What did it suggest as the problems? Did the compiler get confused and diagnose more than four errors? Remove the errors one by one, starting with the lexically first, and see how the error messages change (and improve).

## [Try This 6](try_this/06/01.cpp)
Run this program with a variety of inputs:

- Small values (e.g., 2 and 3).
 - Large values (larger than 127, larger than 1000).
 - Negative values.
 - `56`, `89`, and `128`.
 - Non-integer values (e.g., `56.9` and `56.2`).

You’ll find that many inputs produce “unreasonable” results when
converted. Basically, we are trying to put a gallon into a pint pot (about 4
liters into a 500ml glass).


## [Drill 1](drill/01/01.cpp)
Write a program that produces a simple form letter based on userinput. Begin by typing the code from §2.1 prompting a user to enter his or her first name and writing “Hello, `first_name`” where `first_name` is the name entered by the user. Then modify your code as follows: change the prompt to “Enter the name of the person you want to write to” and change the output to “Dear `first_name`,”. Don’t forget the comma.

## [Drill 2](drill/02/01.cpp)
Add an introductory line or two, like “How are you? I am fine. I miss you.” Be sure to indent the first line. Add a few more lines of your choosing – it’s your letter.

## [Drill 3](drill/03/01.cpp)
Now prompt the user for the name of another friend and store it in `friend_name`. Add a line to your letter: “Have you seen `friend_name` lately?”

## [Drill 4](drill/04/01.cpp)
Prompt the user to enter the age of the recipient and assign it to an `int` variable `age`. Have your program write “I hear you just had a birthday and you are `age` years old.” If `age` is 0 or less or 110 or more, call `simple_error("you’re kidding!")` using `simple_error()` from `PPP_support`.

## [Drill 5](drill/05/01.cpp)
Add this to your letter:

If your friend is under 12, write “Next year you will be `age+1`.” If your friend is 17, write “Next year you will be able to vote.” If your friend is over 70, write “Are you retired?”

Check your program to make sure it responds appropriately to each kind of value.

## [Drill 6](drill/06/01.cpp)
Add “Yours sincerely,” followed by two blank lines for a signature, followed by your name.


## [Review 1](review/01.txt)
What is meant by the term prompt?

## [Review 2](review/02.txt)
Which operator do you use to read into a variable?

## [Review 3](review/03.txt)
What notations can you use to initialize an object?

## [Review 4](review/04.txt)
If you want the user to input an integer value into your program for a variable named `number`, what are two lines of code you could write to ask the user to do it and to input the value into your program?

## [Review 5](review/05.txt)
What is `\n` called and what purpose does it serve?

## [Review 6](review/06.txt)
What terminates input into a string?

## [Review 7](review/07.txt)
What terminates input into an integer?

## [Review 8](review/08.txt)
How would you write the following as a single line of code:
```
cout << "Hello, ";
cout << first_name;
cout << "!\n";
```

## [Review 9](review/09.txt)
What is an object?

## [Review 10](review/10.txt)
What is a literal?

## [Review 11](review/11.txt)
What kinds of literals are there?

## [Review 12](review/12.txt)
What is a variable?

## [Review 13](review/13.txt)
What are typical sizes for a `char`, an `int`, and a `double`?

## [Review 14](review/14.txt)
What measures do we use for the size of small entities in memory, such as `int`s and `string`s?

## [Review 15](review/15.txt)
What is the difference between `=` and `==`?

## [Review 16](review/16.txt)
What is a definition?

## [Review 17](review/17.txt)
What is an initialization and how does it differ from an assignment?

## [Review 18](review/18.txt)
What is string concatenation and how do you make it work in C++?

## [Review 19](review/19.txt)
What operators can you apply to an `int`?

## [Review 20](review/20.txt)
Which of the following are legal names in C++? If a name is not legal, why not?

`This_little_pig`, `This_1_is fine`, `2_For_1_special`, `latest thing`, `George@home`, `_this_is_ok`, `MineMineMine`, `number`, `correct?`, `stroustrup.com`, `$PATH`

## [Review 21](review/21.txt)
Give five examples of legal names that you shouldn’t use because they are likely to cause confusion.

## [Review 22](review/22.txt)
What are some good rules for choosing names?

## [Review 23](review/23.txt)
What is type safety and why is it important?

## [Review 24](review/24.txt)
Why can conversion from `double` to `int` be a bad thing?

## [Review 25](review/25.txt)
Define a rule to help decide if a conversion from one type to another is safe or unsafe.

## [Review 26](review/26.txt)
How can we avoid undesirable conversions?

## [Review 27](review/27.txt)
What are the uses of `auto`?


## Exercise 1
If you haven’t done so already, do the `TRY THIS` exercises from this chapter.

## [Exercise 2](exercises/02/01.cpp)
Write a program in C++ that converts from miles to kilometers. Your program should have a reasonable prompt for the user to enter a number of miles. Hint: A mile is 1.609 kilometers.

## [Exercise 3](exercises/03/01.cpp)
Write a program that doesn’t do anything, but declares a number of variables with legal and illegal names (such as `int double = 0;`), so that you can see how the compiler reacts.

## [Exercise 4](exercises/04/01.cpp)
Write a program that prompts the user to enter two integer values. Store these values in `int` variables named `val1` and `val2`. Write your program to determine the smaller, larger, sum, difference, product, and ratio of these values and report them to the user.

## [Exercise 5](exercises/05/01.cpp)
Modify the program above to ask the user to enter floating-point values and store them in `double` variables. Compare the outputs of the two programs for some inputs of your choice. Are the results the same? Should they be? What’s the difference?

## [Exercise 6](exercises/06/01.cpp)
Write a program that prompts the user to enter three integer values, and then outputs the values in numerical sequence separated by commas. So, if the user enters the values `10 4 6`, the output should be `4, 6, 10`. If two values are the same, they should just be ordered together. So, the input `4 5 4` should give `4, 4, 5`.

## [Exercise 7](exercises/07/01.cpp)
Do exercise 6, but with three string values. So, if the user enters the values `Steinbeck, Hemingway, Fitzgerald`, the output should be `Fitzgerald, Hemingway, Steinbeck`.

## [Exercise 8](exercises/08/01.cpp)
Write a program to test an integer value to determine if it is odd or even. As always, make sure your output is clear and complete. In other words, don’t just output `yes` or `no`. Your output should stand alone, like `The value 4 is an even number`. Hint: See the remainder (modulo) operator in §2.4.

## [Exercise 9](exercises/09/01.cpp)
Write a program that converts spelled-out numbers such as “zero” and “two” into digits, such as 0 and 2. When the user inputs a number, the program should print out the corresponding digit. Do it for the values 0, 1, 2, 3, and 4 and write out `not a number I know` if the user enters something that doesn’t correspond, such as `stupid computer!`.

## [Exercise 10](exercises/10/01.cpp)
Write a program that takes an operation followed by two operands and outputs the result. For example:
```
+ 100 3.14
* 45
```
Read the operation into a string called `operation` and use an if-statement to figure out which operation the user wants, for example, `if (operation=="+")`. Read the operands into variables of type `double`. Implement this for operations called `+, −, *, /, plus, minus, mul,` and `div` with their obvious meanings.

## [Exercise 11](exercises/11/01.cpp)
Write a program that prompts the user to enter some number of pennies (1-cent coins), nickels (5-cent coins), dimes (10-cent coins), quarters (25-cent coins), half dollars (50-cent coins), and one-dollar coins (100- cent coins). Query the user separately for the number of each size coin, e.g., “How many pennies do you have?” Then your program should print out something like this:
```
You have 23 pennies.
You have 17 nickels.
You have 14 dimes.
You have 7 quarters.
You have 3 half dollars.
The value of all of your coins is 573 cents.
```
Make some improvements: if only one of a coin is reported, make the output grammatically correct, e.g., `14 dimes` and `1 dime` (not `1 dimes`). Also, report the sum in dollars and cents, i.e., `.73` instead of `573 cents`.
