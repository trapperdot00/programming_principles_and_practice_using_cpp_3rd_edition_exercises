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

## [Exercise 1](exercises/01/01.cpp)
Here is another way of defining a factorial function:
```
int fac(int n) { return n>1 ? n*fac(n-1) : 1; } // factorial n!
```
It will do `fac(4)` by first deciding that since `4>1` it must be `4*fac(3)`, and that's obviously `4*3*fac(2)`, which again is `4*3*2*fac(1)`, which is `4*3*2*1`. Try to see that it works. A function that calls itself is said to be recursive. The alternative implementation in §13.5 is called iterative because it iterates through the values (using `while`). Verify that the recursive `fac()` works and gives the same results as the iterative `fac()` by calculating the factorial of 0, 1, 2, 3, 4, up until and including 20. Which implementation of `fac()` do you prefer, and why?

## [Exercise 2](exercises/02)
Define a class `Fct` that is just like `Function` except that it stores its constructor arguments. Provide `Fct` with "reset" operations, so that you can use it repeatedly for different ranges, different functions, etc.

## [Exercise 3](exercises/03)
Modify `Fct` from the previous exercise to take an extra argument to control precision or whatever. Make the type of that argument a template parameter for extra flexibility.

## [Exercise 4](exercises/04)
Graph a sine (`sin()`), a cosine (`cos()`), the sum of those (`sin(x)+cos(x)`), and the sum of the squares of those (`sin(x)*sin(x)+cos(x)*cos(x)`) on a single graph. Do provide axes and labels.

## [Exercise 5](exercises/05)
"Animate" (as in §13.5) the series `1-1/3+1/5-1/7+1/9-1/11+ ...`. It is known as Leibniz's series and converges to pi/4.

## [Exercise 6](exercises/06)
Design and implement a bar graph class. Its basic data is a `vector<double>` holding N values, and each value should be represented by a "bar" that is a rectangle where the height represents the value.

## [Exercise 7](exercises/07)
Elaborate the bar graph class to allow labeling of the graph itself and its individual bars. Allow the use of color.

## [Exercise 8](exercises/08)
Here is a collection of heights in centimeters together with the number of people in a group of that height (rounded to the nearest 5cm): (170,7, (175,9), (180,23), (185,17), (190,6), 195,1). How would you graph that data? If you can't think of anything better, do a bar graph. Remember to provide axes and labels. Place the data in a file and read it from that file.

## [Exercise 9](exercises/09)
Find another data set of heights (an inch is 2.54cm) and graph them with your program from the previous exercise. For example, search the Web for "height distribution" or "height of people in the United States" and ignore a lot of rubbish or ask your friends for their heights. Ideally, you don't have to change anything for the new data set. Calculating the scaling from the data is a key idea. Reading in labels from input also helps minimize changes when you want to reuse code.

## [Exercise 10](exercises/10)
What kind of data is unsuitable for a line graph or a bar graph? Find an example and find a way of displaying it (e.g., as a collection of labeled points).

## [Exercise 11](exercises/11)
Find the average maximum temperatures for each month of the year for two or more locations (e.g., Cambridge, England, and Cambridge, Massachusetts; there are lots of towns called "Cambridge") and graph them together. As ever, be careful with axes, labels, use of color, etc.
