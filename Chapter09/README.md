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

## [Drill 11](drill/11)
Defining a data type `Point` that has two coordinate members `x` and `y`. Define `<<` and `>>` for `Point` as discussed in §9.3.1.

## [Drill 12](drill/12)
Using the code and discussion in §9.3.1, prompt the user to input seven (x,y) pairs. As the data is entered, store it in a `vector<Point>` called `original_points`.

## [Drill 13](drill/13)
Print the data in `original_points` to see what it looks like.

## [Drill 14](drill/14)
Open an `ofstream` and output each point to a file named `mydata.txt`. We suggest the `.txt` suffix to make it easier to look at the data with an ordinary text editor if you are using Windows.

## [Drill 15](drill/15)
Open an `ifstream` for `mydata.txt`. Read the data from `mydata.txt` and store it in a new vector called `processed_points`.

## [Drill 16](drill/16)
Print the data elements from both `vector`s.

## [Drill 17](drill/17)
Compare the two `vector`s and print “Something’s wrong!” if the number of elements or the values of elements differ.


## [Review 1](review/01.txt)
Why is I/O tricky for a programmer?

## [Review 2](review/02.txt)
What does the notation `<< hex` do?

## [Review 3](review/03.txt)
What are hexadecimal numbers used for in computer science? Why?

## [Review 4](review/04.txt)
Name some of the options you may want to implement for formatting integer output.

## [Review 5](review/05.txt)
What is a manipulator?

## [Review 6](review/06.txt)
What is the default output format for floating-point values?

## [Review 7](review/07.txt)
Explain what `setprecision()` and `setw()` do.

## [Review 8](review/08.txt)
Which of the following manipulators do not “stick”: `hex`, `scientific`, `setprecision()`, `setw()`?

## [Review 9](review/09.txt)
In `format()`, how do you specify where an argument is placed on output?

## [Review 10](review/10.txt)
Give two examples where a `stringstream` can be useful.

## [Review 11](review/11.txt)
When would you prefer line-oriented input to type-specific input?

## [Review 12](review/12.txt)
What does `isalnum(c)` do?

## [Review 13](review/13.txt)
When dealing with input and output, how is the variety of devices dealt with in most modern computers?

## [Review 14](review/14.txt)
What, fundamentally, does an `istream` do?

## [Review 15](review/15.txt)
What, fundamentally, does an `ostream` do?

## [Review 16](review/16.txt)
What, fundamentally, is a file?

## [Review 17](review/17.txt)
What is a file format?

## [Review 18](review/18.txt)
Name four different types of devices that can require I/O for a program.

## [Review 19](review/19.txt)
What are the four steps for reading a file?

## [Review 20](review/20.txt)
What are the four steps for writing a file?

## [Review 21](review/21.txt)
Name and define the four stream states.

## [Review 22](review/22.txt)
Discuss how the following input problems can be resolved:
```
a. The user typing an out-of-range value
b. Getting no value (end-of-file)
c. The user typing something of the wrong type
```

## [Review 23](review/23.txt)
In what way is input usually harder than output?

## [Review 24](review/24.txt)
In what way is output usually harder than input?

## [Review 25](review/25.txt)
Why do we (often) want to separate input and output from computation?

## [Review 26](review/26.txt)
What are the two most common uses of the `istream` member function `clear()`?

## [Review 27](review/27.txt)
What are the usual function declarations for `<<` and `>>` for a user-defined type `X`?

## [Review 28](review/28.txt)
How do you specify where an argument is inserted into a format string in `format()`?

## [Review 29](review/29.txt)
What is the notation for bases of decimal values in `format()`?

## [Review 30](review/30.txt)
How do you specify the precision of floating-point values in `format()`?


## [Exercise 1](exercises/01/01.cpp)
Write a program that reads a text file and converts its input to all lowercase, producing a new file.

## [Exercise 2](exercises/02/01.cpp)
Write a program that given a file name and a word will output each line that contains that word together with the line number. Hint: `getline()`.

## [Exercise 3](exercises/03/01.cpp)
Write a program that removes all vowels from a file ("disemvowels"). For example, `Once upon a time!` becomes `nc pn tm!`. Surprisingly often, the result is still readable; try it on your friends.

## [Exercise 4](exercises/04/multi_input.cpp)
Write a program called `multi_input.cpp` that prompts the user to enter several integers in any combination of octal, decimal, or hexadecimal, using the `0` and `0x` base prefixes; interprets the numbers correctly; and converts them to decimal form. Then your program should output the values in properly spaced columns like this:
```
0x43    hexadecimal     converts to     67  decimal
0123    octal           converts to     83  decimal
65      decimal         converts to     65  decimal
```

## [Exercise 5](exercises/05/01.cpp)
Write a program that reads strings and for each string outputs the character classification of each character, as defined by the character classification functions presented in §9.10.3. Note that a character can have several classifications (e.g., `x` is both a letter and an alphanumeric).

## [Exercise 6](exercises/06/01.cpp)
Write a program that replaces punctuation with whitespace. Consider `.` (dot), `;` (semicolon), `,` (comma), `?` (question mark), `−` (dash), `’` (single quote) punctuation characters. Don’t modify characters within a pair of double quotes (`"`). For example, “`− don’t use the as−if rule.`” becomes “`don t use the as if rule `”.

## [Exercise 7](exercises/07/01.cpp)
Modify the program from the previous exercise so that it replaces `don’t` with `do not`, `can’t` with `cannot`, etc.; leaves hyphens within words intact (so that we get “`do not use the as−if rule `”); and converts all characters to lowercase.

## [Exercise 8](exercises/08)
Use the program from the previous exercise to make a sorted list of words. Run the result on a multi-page text file, look at the result, and see if you can improve the program to make a better list.

## [Exercise 9](exercises/09/01.cpp)
Write a function `vector<string> split(const string& s)` that returns a `vector` of whitespace-separated substrings from the argument `s`.

## [Exercise 10](exercises/10/01.cpp)
Write a function `vector<string> split(const string& s, const string& w)` that returns a `vector` of whitespace-separated substrings from the argument `s`, where whitespace is defined as “ordinary whitespace” plus the characters in `w`.

## [Exercise 11](exercises/11/01.cpp)
Reverse the order of characters in a text file. For example, `asdfghjkl` becomes `lkjhgfdsa`. Warning: There is no really good, portable, and efficient way of reading a file backward.

## [Exercise 12](exercises/12/01.cpp)
Reverse the order of words (defined as whitespace-separated strings) in a file. For example, `Norwegian Blue parrot` becomes `parrot Blue Norwegian`. Assume that all the strings from the file will fit into memory at once.

## [Exercise 13](exercises/13/01.cpp)
Write a program that reads a text file and writes out how many characters of each character classification (§9.10.3) are in the file.

## [Exercise 14](exercises/14/01.cpp)
Write a program that reads a file of whitespace-separated numbers and outputs a file of numbers using scientific format and precision 8 in four fields of 20 characters per line.

## [Exercise 15](exercises/15/01.cpp)
Write a program to read a file of whitespace-separated numbers and output them in order (lowest value first), one value per line. Write a value only once, and if it occurs more than once write the count of its occurrences on its line. For example, `75573 117 5` should give
```
3
5   3
7   2
117
```

## [Exercise 16](exercises/16/01.cpp)
Write a program that produces the sum of all the numbers in a file of whitespace-separated integers.

## [Exercise 17](exercises/17)
Write a program that creates a file of data in the form of the temperature `Reading` type defined in §9.3.2. For testing, fill the file with at least 50 “temperature readings.” Call this program `store_temps.cpp` and the file it creates `raw_temps.txt`.
