# 13: Graphing Functions and Data

- [Drill](#drill-1)
- [Review](#review-1)
- [Terms](terms.txt)
- [Exercises](#exercise-1)

## [Drill 1](drill/01)
Make an empty 600-by-600 `Window` labeled "Function graphs".

## [Drill 2](drill/02)
Add an x axis and a y axis each of length 400, labeled "1 == 20 pixels" and with a notch every 20 pixels. The axes should cross at (300,300).

## [Drill 3](drill/03)
Make both axes red.

## [Drill 4](drill/04)
Graph the function `double one(double x) { return 1; }` in the range [-10,11] with (0,0) at (300,300) using 400 points and no scaling (in the window).

## [Drill 5](drill/05)
Change it to use x scale 20 and y scale 20.

## [Drill 6](drill/06)
From now on use that range, scale, etc. for all graphs.

## [Drill 7](drill/07)
Add `double slope(double x) { return 0.5*x; }` to the window.

## [Drill 8](drill/08)
Label the slope with a `Text "0.5x"` at a point just above its bottom left end point.

## [Drill 9](drill/09)
Add `double square(double x) { return x * x; }` to the window.

## [Drill 10](drill/10)
Add a cosine to the window (don't write a new function).

## [Drill 11](drill/11)
Make the cosine blue.

## [Drill 12](drill/12)
Write a function `sloping_cos()` that adds a cosine to `slope()` (as defined above) and add it to the window.

## [Drill 13](drill/13)
Define a `struct Person` containing a `string` name and an `int` age.

## [Drill 14](drill/14)
Define a variable of type `Person`, initialize it with "Goofy" and 63, and write it to the screen (`cout`).

## [Drill 15](drill/15)
Define an input (`>>`) and an output (`<<`) operator for `Person`; read in a `Person` from the keyboard (`cin`) and write it out to the screen (`cout`).

## [Drill 16](drill/16)
Give `Person` a constructor initializing `name` and `age`.

## [Drill 17](drill/17)
Make the representation of `Person` private, and provide `const` member functions `name()` and `age()` to read the name and age.

## [Drill 18](drill/18)
Modify `>>` and `<<` to work with the redefined `Person`.

## [Drill 19](drill/19)
Modify the constructor to check that `age` is [0:150) and that `name` doesn't contain any of the characters `;:"'[]*&^%$#@!`. Use `error()` in case of error. Test.

## [Drill 20](drill/20)
Read a sequence of `Person`s from input (`cin`) into a `vector<Person>`; write them out again to the screen (`cout`). Test with correct and erroneous input.

## [Drill 21](drill/21)
Change the representation of `Person` to have `first_name` and `second_name` instead of `name`. Make it an error not to supply both a first and a second name. Be sure to fix `>>` and `<<` also. Test.


## [Review 1](review/01.txt)
What is a function of one argument?

## [Review 2](review/02.txt)
When would you use a (continuous) line to represent data? When do you use (discrete) points?

## [Review 3](review/03.txt)
What function (mathematical formula) defines a slope?

## [Review 4](review/04.txt)
What is a parabola?

## [Review 5](review/05.txt)
How do you make an x axis? A y axis?

## [Review 6](review/06.txt)
What is a default argument and when would you use one?

## [Review 7](review/07.txt)
How do you add functions together?
 
## [Review 8](review/08.txt)
How do you color and label a graphed function?

## [Review 9](review/09.txt)
What do we mean when we say that a series approximates a function?

## [Review 10](review/10.txt)
Why would you sketch out the layout of a graph before writing the code to draw it?

## [Review 11](review/11.txt)
How would you scale your graph so that the input will fit?

## [Review 12](review/12.txt)
How would you scale the input without trial and error?

## [Review 13](review/13.txt)
Why would you format your input rather than just having the file contain "the numbers"?

## [Review 14](review/14.txt)
How do you plan the general layout of a graph? How do you reflect that layout in your code?
