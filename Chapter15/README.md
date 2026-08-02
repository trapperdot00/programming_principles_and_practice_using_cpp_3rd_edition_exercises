# 15: Vector and Free Store

- [Try This](#try-this-1)
- [Drill](#drill-11)
- [Review](#review-1)
- [Terms](terms.txt)
- [Exercises](#exercise-1)

## [Try This 1](try_this/01/main.cpp)
Execute the example above and see what you get.
Then extend the example to determine the size of `bool`, `double`, and some other type.

## [Try This 2](try_this/02/main.cpp)
Write a little program using base classes and members where you define the constructors and destructors to output a line of information when they are called.
Then, create a few objects and see how their constructors and destructors are called.


## [Drill 1.1](drill/1/01/main.cpp)
Allocate an array of ten `int`s on the free store using `new`.

## [Drill 1.2](drill/1/02/main.cpp)
Print the values of the ten `int`s to `cout`.

## [Drill 1.3](drill/1/03/main.cpp)
Deallocate the array (using `delete[]`).

## [Drill 1.4](drill/1/04/main.cpp)
Write a function `print_array(ostream& os, int* a, int n)` that prints out the values of `a` (assumed to have `n` elements) to `os`.

## [Drill 1.5](drill/1/05/main.cpp)
Allocate an array of ten `int`s on the free store; initialize it with the values 100, 101, 102, etc.; and print out its values.

## [Drill 1.6](drill/1/06/main.cpp)
Allocate an array of 11 `int`s on the free store; initialize it with the values 100, 101, 102, etc.; and print out its values.

## [Drill 1.7](drill/1/07/main.cpp)
Allocate an array of 20 `int`s on the free store; initialize it with the values 100, 101, 102, etc.; and print out its values.

## Drill 1.8
Did you remember to delete the arrays? (If not, do it.)

## [Drill 1.9](drill/1/09/main.cpp)
Do 5, 6, and 7 using a `vector` instead of an array and a `print_vector()` instead of `print_array()`.

## [Drill 2.1](drill/2/01)
Allocate an `int`, initialize it to 7, and assign its address to a variable `p1`.

## [Drill 2.2](drill/2/02)
Print out the value of `p1` and of the `int` it points to.

## [Drill 2.3](drill/2/03)
Allocate an array of seven `int`s; initialize it to 1, 2, 4, 8, etc.; and assign its address to a variable `p2`.

## [Drill 2.4](drill/2/04)
Print out the value of `p2` and of the array it points to.

## [Drill 2.5](drill/2/05)
Declare an `int*` called `p3` and initialize it with `p2`.
