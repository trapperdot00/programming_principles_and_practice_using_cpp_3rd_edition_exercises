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
