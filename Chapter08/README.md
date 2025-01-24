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
