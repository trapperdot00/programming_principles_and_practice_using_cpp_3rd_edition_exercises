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
