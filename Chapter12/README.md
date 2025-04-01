# 12: Class Design

- [Drill](#drill-1)
- [Review](#review-1)
- [Terms](terms.txt)
- [Exercises](#exercise-1)

## [Drill 1](drill/01)
Deﬁne a class `B1` with a virtual function `vf()` and a non-virtual function `f()`. Deﬁne both of these functions within class `B1`. Implement each function to output its name (e.g., `B1::vf()`). Make the functions `public`. Make a `B1` object and call each function.

## [Drill 2](drill/02)
Derive a class `D1` from `B1` and override `vf()`. Make a `D1` object and call `vf()` and `f()` for it.

## [Drill 3](drill/03)
Deﬁne a reference to `B1` (a `B1&`) and initialize that to the `D1` object you just deﬁned. Call `vf()` and `f()` for that reference.

## [Drill 4](drill/04)
Now deﬁne a function called `f()` for `D1` and repeat 1–3. Explain the results.

## [Drill 5](drill/05)
Add a pure virtual function called `pvf()` to `B1` and try to repeat 1–4. Explain the result.

## [Drill 6](drill/06)
Deﬁne a class `D2` derived from `D1` and override `pvf()` in `D2`. Make an object of class `D2` and invoke `f()`, `vf()`, and `pvf()` for it.

## [Drill 7](drill/07)
Deﬁne a class `B2` with a pure virtual function `pvf()`. Deﬁne a class `D21` with a `string` data member and a member function that overrides `pvf()`; `D21::pvf()` should output the value of the `string`. Deﬁne a class `D22` that is just like `D21` except that its data member is an `int`. Deﬁne a function `f()` that takes a `B2&` argument and calls `pvf()` for its argument. Call `f()` with a `D21` and a `D22`.


## [Review 1](review/01.txt)
What is an application domain?

## [Review 2](review/02.txt)
What are ideals for naming?

## [Review 3](review/03.txt)
What can we name?

## [Review 4](review/04.txt)
What services does a `Shape` offer?

## [Review 5](review/05.txt)
How does an abstract class differ from a class that is not abstract?

## [Review 6](review/06.txt)
How can you make a class abstract?

## [Review 7](review/07.txt)
What is controlled by access control?

## [Review 8](review/08.txt)
What good can it do to make a data member `private`?

## [Review 9](review/09.txt)
What is a virtual function and how does it differ from a non-virtual function?

## [Review 10](review/10.txt)
What is a base class?

## [Review 11](review/11.txt)
What makes a class derived?

## [Review 12](review/12.txt)
What do we mean by object layout?

## [Review 13](review/13.txt)
What can you do to make a class easier to test?

## [Review 14](review/14.txt)
What is an inheritance diagram?

## [Review 15](review/15.txt)
What is the difference between a `protected` member and a `private` one?

## [Review 16](review/16.txt)
What members of a class can be accessed from a class derived from it?

## [Review 17](review/17.txt)
How does a pure virtual function differ from other virtual functions?

## [Review 18](review/18.txt)
Why would you make a member function virtual?

## [Review 19](review/19.txt)
Why would you not make a member function virtual?

## [Review 20](review/20.txt)
Why would you make a virtual member pure?

## [Review 21](review/21.txt)
What does overriding mean?

## [Review 22](review/22.txt)
Why should you always suppress copy operations for a class in a class hierarchy?

## [Review 23](review/23.txt)
How does interface inheritance differ from implementation inheritance?

## [Review 24](review/24.txt)
What is object-oriented programming?


## [Exercise 1](exercises/01)
Define two classes `Smiley` and `Frowny`, which are both derived from class `Circle` and have two eyes and a mouth. Next, derive classes from `Smiley` and `Frowny` which add an appropriate hat to each.

## [Exercise 2](exercises/02)
Try to copy a `Shape`. What happens?

## [Exercise 3](exercises/03)
Define an abstract class and try to define an object of that type. What happens?

## [Exercise 4](exercises/04)
Define a class `Immobile_Circle`, which is just like `Circle` but can't be moved.

## [Exercise 5](exercises/05)
Define a `Striped_rectangle` where instead of fill, the rectangle is "filled" by drawing one-pixel-wide horizontal lines across the inside of the rectangle (say, draw every second line like that). You may have to play with the width of lines and the line spacing to get a pattern you like.

## [Exercise 6](exercises/06)
Define a `Striped_circle` using the technique from `Striped_rectangle`.

## [Exercise 7](exercises/07)
Define a `Striped_closed_polyline` using the technique from `Striped_rectangle` (this requires some algorithmic inventiveness).

## [Exercise 8](exercises/08)
Define a class `Octagon` to be a regular octagon. Write a test that exercises all of its functions (as defined by you or inherited from `Shape`).
