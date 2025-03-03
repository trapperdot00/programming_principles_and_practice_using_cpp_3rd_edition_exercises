# 11: Graphics Classes

- [Try This](#try-this-1)
- [Drill](#drill-1)
- [Review](#review-1)
- [Terms](terms.txt)
- [Exercises](#exercise-1)

## [Try This 1](try_this/01)
Replicate the grid example as above but use a different color and a different line style.

## [Try This 2](try_this/02)
Write, compile, and run a simple program displaying a picture of your choice. Did it fit in your window? If not, what happened?


## [Drill 1](drill/01)
Make an 800-by-1000 `Simple_window`.

## [Drill 2](drill/02)
Put an 8-by-8 grid on the leftmost 800-by-800 part of that window (so that each square is 100 by 100).

## [Drill 3](drill/03)
Make the eight squares on the diagonal starting from the top left corner red (use `Rectangle`).

## [Drill 4](drill/04)
Find a 200-by-200-pixel image (JPEG or GIF) and place three copies ofit on the grid (each image covering four squares). If you can’t find an image that is exactly 200 by 200, use `set_mask()` to pick a 200-by-200 section of a larger image. Don’t obscure the red squares.

## [Drill 5](drill/05)
Add a 100-by-100 image. Have it move around from square to square when you click the “Next” button. Just put `wait_for_button()` in a loop with some code that picks a new square for your image.


## [Review 1](review/01.txt)
Why don’t we “just” use a commercial or open-source graphics library directly?

## [Review 2](review/02.txt)
About how many classes from our graphics interface library do you need to do simple graphics output?

## [Review 3](review/03.txt)
What are the header files needed to use the graphics interface library?

## [Review 4](review/04.txt)
What classes define closed shapes?

## [Review 5](review/05.txt)
Why don’t we just use `Line` for every shape?

## [Review 6](review/06.txt)
What do the arguments to `Point` indicate?

## [Review 7](review/07.txt)
What are the components of `Line_style`?

## [Review 8](review/08.txt)
What are the components of `Color`?

## [Review 9](review/09.txt)
What is RGB?

## [Review 10](review/10.txt)
What are the differences between two `Line`s and a `Lines` containing two lines?

## [Review 11](review/11.txt)
What properties can you set for every `Shape`?

## [Review 12](review/12.txt)
How many sides does a `Closed_polyline` defined by five `Point`s have?

## [Review 13](review/13.txt)
What do you see if you define a `Shape` but don’t attach it to a `Window`?

## [Review 14](review/14.txt)
How does a `Rectangle` differ from a `Polygon` with four `Point`s (corners)?

## [Review 15](review/15.txt)
How does a `Polygon` differ from a `Closed_polyline`?

## [Review 16](review/16.txt)
What’s on top: fill or outline?

## [Review 17](review/17.txt)
Why didn’t we bother defining a `Triangle` class (after all, we did define `Rectangle`)?

## [Review 18](review/18.txt)
How do you move a `Shape` to another place in a `Window`?

## [Review 19](review/19.txt)
How do you label a `Shape` with a line of text?

## [Review 20](review/20.txt)
What properties can you set for a text string in a `Text`?

## [Review 21](review/21.txt)
What is a font and why do we care?

## [Review 22](review/22.txt)
What is `Vector_ref` for and how do we use it?

## [Review 23](review/23.txt)
What is the difference between a `Circle` and an `Ellipse`?

## [Review 24](review/24.txt)
What happens if you try to display an `Image` given a file name that doesn’t refer to a file containing an image?

## [Review 25](review/25.txt)
How do you display part of an `Image`?

## [Review 26](review/26.txt)
How do you scale an `Image`?


## [Exercise 1](exercises/01)
Define a class `Arrow`, which draws a line with an arrowhead.

## [Exercise 2](exercises/02)
Define functions `n()`, `s()`, `e()`, `w()`, `center()`, `ne()`, `se()`, `sw()`, and `nw()`. Each takes a `Rectangle` argument and returns a `Point`. These functions define “connection points” on and in the rectangle. For example, `nw(r)` is the northwest (top left) corner of a `Rectangle` called `r`.

## [Exercise 3](exercises/03)
Define the functions from exercise 2 for a `Circle` and an `Ellipse`. Place the connection points on or outside the shape but not outside the bounding rectangle.

## [Exercise 4](exercises/04)
Write a program that draws a class diagram like the one in §10.6. It will simplify matters if you start by defining a `Box` class that is a rectangle with a text label.

## [Exercise 5](exercises/05)
Make an RGB color chart (e.g., search the Web for “RGB color chart”).

## [Exercise 6](exercises/06)
Define a class `Regular_hexagon` (a regular hexagon is a six-sided polygon with all sides of equal length). Use the center and the distance from the center to a corner point as constructor arguments.

## [Exercise 7](exercises/07)
Tile a part of a window with `Regular_hexagons` (use at least eight hexagons).
