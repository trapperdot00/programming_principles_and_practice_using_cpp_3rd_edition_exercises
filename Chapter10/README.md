# 10: A Display Model

- [Drill](#drill-1)
- [Review](#review-1)
- [Terms](terms.txt)
- [Exercises](#exercise-1)

## [Drill 1](drill/01)
Get an empty `Simple_window` with the size 600 by 400 and a label `My window` compiled, linked, and run. Note that you have to link the Qt library, `#include Graph.h` and `Simple_window.h` in your code, and compile and link `Graph.cpp` and `Window.cpp` into your program.

## [Drill 2](drill/02)
Now add the examples from §10.7 one by one, testing between each added subsection example.

## [Drill 3](drill/03)
Go through and make one minor change (e.g., in color, in location, or in number of points) to each of the subsection examples.


## [Review 1](review/01.txt)
Why do we use graphics?

## [Review 2](review/02.txt)
When do we try not to use graphics?

## [Review 3](review/03.txt)
Why is graphics interesting for a programmer?

## [Review 4](review/04.txt)
What is a window?

## [Review 5](review/05.txt)
In which namespace do we keep our graphics interface classes (our graphics library)?

## [Review 6](review/06.txt)
What header files do you need to do basic graphics using our graphics library?

## [Review 7](review/07.txt)
What is the simplest window to use?

## [Review 8](review/08.txt)
What is the minimal window?

## [Review 9](review/09.txt)
What’s a window label?

## [Review 10](review/10.txt)
How do you label a window?

## [Review 11](review/11.txt)
How do screen coordinates work? Window coordinates? Mathematical coordinates?

## [Review 12](review/12.txt)
What are examples of simple “shapes” that we can display?

## [Review 13](review/13.txt)
What command attaches a shape to a window?

## [Review 14](review/14.txt)
Which basic shape would you use to draw a hexagon?

## [Review 15](review/15.txt)
How do you write text somewhere in a window?

## [Review 16](review/16.txt)
How would you put a photo of your best friend in a window (using a program you wrote yourself)?

## [Review 17](review/17.txt)
You made a `Window` object, but nothing appears on your screen. What are some possible reasons for that?

## [Review 18](review/18.txt)
What library do we use to implement our graphics/GUI interface library? Why don’t we use the operating system directly?


## [Exercise 1](exercises/01)
Draw a rectangle as a `Rectangle` and as a `Polygon`. Make the lines of the `Polygon` red and the lines of the `Rectangle` blue.

## [Exercise 2](exercises/02)
Draw a 100-by-30 `Rectangle` and place the text “Howdy!” inside it.

## [Exercise 3](exercises/03)
Draw your initials 150 pixels high. Use a thick line. Draw each initial in a different color.

## [Exercise 4](exercises/04)
Draw a 3-by-3 tic-tac-toe board of alternating white and red squares.

## [Exercise 5](exercises/05)
Draw a red 1/4-inch frame around a rectangle that is three-quarters the height of your screen and two-thirds the width.

## [Exercise 6](exercises/06)
What happens when you draw a `Shape` that doesn’t fit inside its window? What happens when you draw a `Window` that doesn’t fit on your screen? Write two programs that illustrate these two phenomena.

## [Exercise 7](exercises/07)
Draw a two-dimensional house seen from the front, the way a child would: with a door, two windows, and a roof with a chimney. Feel free to add details; maybe have “smoke” come out of the chimney.

## [Exercise 8](exercises/08)
Draw the Olympic five rings. If you can’t remember the colors, look them up.

## [Exercise 9](exercises/09)
Display an image on the screen, e.g., a photo of a friend. Label the image both with a title on the window and with a caption in the window.

## [Exercise 10](exercises/10)
Draw the source file diagram from §10.8.1.

## [Exercise 11](exercises/11)
Draw a series of regular polygons, one inside the other. The innermost should be an equilateral triangle, enclosed by a square, enclosed by a pentagon, etc. For the mathematically adept only: let all the points of each `N`-polygon touch sides of the `(N+1)`-polygon. Hint: The trigonometric functions are found in `<cmath>` and module `std` (PPP2.§24.8).

## [Exercise 12](exercises/12)
A superellipse is a two-dimensional shape defined by the equation `|x/a|^m + |y/b|^n = 1;` where m > 0 and n > 0.
Look up _superellipse_ on the Web to get a better idea of what such shapes look like. Write a program that draws “starlike” patterns by connecting points on a superellipse. Take `a`, `b`, `m`, `n`, and `N` as arguments. Select `N` points on the superellipse defined by `a`, `b`, `m`, and `n`. Make the points equally spaced for some definition of “equal.” Connect each of those `N` points to one or more other points (if you like you can make the number of points to which to connect a point another argument or just use `N–1`, i.e., all the other points).

## [Exercise 13](exercises/13)
Find a way to add color to the lines from the previous exercise. Make some lines one color and other lines another color or other colors.
