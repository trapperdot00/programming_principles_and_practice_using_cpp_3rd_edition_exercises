# 8: Technicalities: Classes, etc.

- [Try This](#try-this-1)
- [Drill](#drill-1)
- [Review](#review-1)
- [Terms](terms.txt)
- [Exercises](#exercise-1)

## [Try This 1](try_this/01/01.cpp)
Get some example uses of a version of `Date` so far to run. For that, we need an output operator for `Date`. There is one in `PPP_support`, but for now use
```
ostream& operator<<(ostream& os, Date d)
{
    return os << d.year() << '/’ << d.month() << '/’ << d.day();
}
```
Chapter 9 explains why and how that works.

## [Try This 2](try_this/02/01.cpp)
Write, compile, and run a small example using `++` and `<<` for `Month`.


## [Drill 1](drill/01/01.cpp)
Write `Day`, `Month`, and their associated functions as described above. Complete the final version of `Date` with default constructor, `is_valid()`, `Month`, `Year`, etc. Define a `Date` called `today` initialized to February 2, 2020. Then, define a `Date` called `tomorrow` and give it a value by copying `today` into it and increasing its day by one using `add_day()`. Finally, output `today` and `tomorrow` using a `<<` defined as in §9.6 and §9.7.
Your check for a valid date, `is_valid()`, may be very simple. Feel free to ignore leap years. However, don’t accept a month that is not in the [1,12] range or a day of the month that is not in the [1,31] range. Test each version with at least one invalid date (e.g., 2004, 13, -5).


## [Review 1](review/01.txt)
What are the two parts of a class, as described in the chapter?

## [Review 2](review/02.txt)
What is the difference between the interface and the implementation in a class?

## [Review 3](review/03.txt)
What are the limitations and problems of the `struct Date` from §8.4.1?

## [Review 4](review/04.txt)
Why is a constructor used for the `Date` type instead of an `init_day()` function?

## [Review 5](review/05.txt)
What is an invariant? Give examples.

## [Review 6](review/06.txt)
When should functions be put in the class definition, and when should they be defined outside the class? Why?

## [Review 7](review/07.txt)
What is a default constructor and when do we need one?

## [Review 8](review/08.txt)
What is a default member initializer?

## [Review 9](review/09.txt)
When should operator overloading be used in a program? Give a list of operators that you might want to overload (each with a reason). Which ones can you define in C++?

## [Review 10](review/10.txt)
Why should the public interface to a class be as small as possible?

## [Review 11](review/11.txt)
What does adding `const` to a member function do?

## [Review 12](review/12.txt)
Why are “helper functions” best placed outside the class definition?

## [Review 13](review/13.txt)
How does an `enum class` differ from a “plain” `enum`?


## [Exercise 1](exercises/01/01.txt)
List plausible operations for the examples of real-world objects in §8.1 (e.g., a toaster).

## [Exercise 2](exercises/02)
Design and implement a `Name_pairs` class holding (name,age) pairs where name is a `string` and age is a `double`. Represent that as a `vector<string>` (called `name`) and a `vector<double>` (called `age`) member. Provide an input operation `read_names()` that reads a series of names. Provide a `read_ages()` operation that prompts the user for an age for each name. Provide a `print()` operation that prints out the (`name[i],age[i]`) pairs (one per line) in the order determined by the `name` vector. Provide a `sort()` operation that sorts the `name` vector in alphabetical order and reorganizes the `age` vector to match. Implement all “operations” as member functions. Test the class (of course: test early and often).

## [Exercise 3](exercises/03)
Replace `Name_pair::print()` with a (global) operator `<<` and define `==` and `!=` for `Name_pairs`.

## [Exercise 4](exercises/04)
Do the previous exercise again but implement `Name_pairs` using a `Name_pair` class.

## [Exercise 5](exercises/05)
This exercise and the next few require you to design and implement a `Book` class, such as you can imagine as part of software for a library. Class `Book` should have members for the ISBN, title, author, and copyright date. Also store data on whether or not the book is checked out. Create functions for returning those data values. Create functions for checking a book in and out. Do simple validation of data entered into a `Book`; for example, accept ISBNs only of the form `n−n−n−x` where `n` is an integer and `x` is a digit or a letter. Store an ISBN as a `string`.

## [Exercise 6](exercises/06)
Add operators for the `Book` class. Have the `==` operator check whether the ISBN numbers are the same for two books. Have `!=` also compare the ISBN numbers. Have a `<<` print out the title, author, and ISBN on separate lines.

## [Exercise 7](exercises/07)
Create an enumerated type for the `Book` class called `Genre`. Have the types be fiction, nonfiction, periodical, biography, and children. Give each book a `Genre` and make appropriate changes to the `Book` constructor and member functions.
