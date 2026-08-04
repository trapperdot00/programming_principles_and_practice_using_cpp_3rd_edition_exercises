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

## [Drill 2.6](drill/2/06)
Assign `p1` to `p2`.

## [Drill 2.7](drill/2/07)
Assign `p3` to `p2`.

## [Drill 2.8](drill/2/08)
Print out the values of `p1` and `p2` and of what they point to.

## [Drill 2.9](drill/2/09)
Deallocate all the memory you allocated from the free store.

## [Drill 2.10](drill/2/10)
Allocate an array of ten `int`s; initialize it to 1, 2, 4, 8, etc.; and assign its address to `p1`.

## [Drill 2.11](drill/2/11)
Allocate an array of ten `int`s; and assign its address to a variable `p2`.

## [Drill 2.12](drill/2/12)
Copy the values from the array pointed to by `p1` into the array pointed to by `p2`.

## [Drill 2.13](drill/2/13)
Repeat 10-12 using a `vector` rather than an array.


## [Exercise 1](exercises/01/main.cpp)
What is the output format of pointer values on your implementation?
Hint: Don't read the documentation.

## [Exercise 2](exercises/02/main.cpp)
How many bytes are there in an `int`?
In a `double`?
In a `bool`?
Do not use `sizeof` except to verify your answer.

## [Exercise 3](exercises/03/main.cpp)
List two ways that a pointer can be misused in potentially disastrous ways.
Give examples.

## [Exercise 4](exercises/04/main.cpp)
Consider the memory layout in §15.4.
Write a program that tells the order in which static storage, the stack, and the free store are laid out in memory.
In which direction does the stack grow: upward toward higher addresses or downward toward lower addresses?
In an array on the free store, are elements with higher indices allocated at higher or lower addresses?
