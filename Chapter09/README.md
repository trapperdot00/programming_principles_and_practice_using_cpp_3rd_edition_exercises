# 9: Input and Output Streams

- [Try This](#try-this-1)
- [Drill](#drill-1)
- [Review](#review-1)
- [Terms](terms.txt)
- [Exercises](#exercise-1)

## [Try This 1](try_this/01/01.cpp)
Output your birth year in decimal, hexadecimal, and octal form. Label each value. Line up your output in columns using the tab character. Now output your age.

## [Try This 2](try_this/02/01.cpp)
See what that last statement prints, and explain it. Try some other formats.


## [Drill 1](drill/01/Test_output.cpp)
Start a program called `Test_output.cpp`. Declare an integer `birth_year` and assign it the year you were born.

## [Drill 2](drill/02/Test_output.cpp)
Output your `birth_year` in decimal, hexadecimal, and octal form.

## [Drill 3](drill/03/Test_output.cpp)
Label each value with the name of the base used.

## [Drill 4](drill/04/Test_output.cpp)
Did you line up your output in columns using the tab character? If not, do it.

## [Drill 5](drill/05/Test_output.cpp)
Now output your age.

## [Drill 6](drill/06/Test_output.cpp)
Was there a problem? What happened? Fix your output to decimal.

## [Drill 7](drill/07/Test_output.cpp)
Go back to 2 and cause your output to show the base for each output.

## [Drill 8](drill/08/01.cpp)
Try reading as octal, hexadecimal, etc.:
```
cin >> a >>oct >> b >> hex >> c >> d;
cout << a << '\t'<< b << '\t'<< c << '\t'<< d << '\n';
```
Run this code with the input
```
1234 1234 1234 1234
```
Explain the results.

## [Drill 9](drill/09/01.cpp)
Write some code to print the number `1234567.89` three times, first using `defaultfloat`, then `fixed`, then `scientific` forms. Which output form presents the user with the most accurate representation? Explain why.

## [Drill 10](drill/10/01.cpp)
Make a simple table including last name, first name, telephone number, and email address for yourself and at least five of your friends. Use `string`s to hold all values, even for the phone numbers. Experiment with different field widths until you are satisfied that the table is well presented.
