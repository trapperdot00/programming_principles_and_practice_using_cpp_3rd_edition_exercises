# 14: Graphical User Interfaces

- [Drill](#drill-1)
- [Review](#review-1)
- [Terms](terms.txt)
- [Exercises](#exercise-1)

## [Drill 1](drill/01)
Make a completely new project with linker settings for Qt (`www.stroustrup.com/programming.html`).

## [Drill 2](drill/02)
Using the facilities of `Graph_lib`, type in the line-drawing program from §14.5 and get it to run.

## [Drill 3](drill/03)
Modify the program to use a pop-up menu as described in §14.5.2 and get it to run.

## [Drill 4](drill/04)
Modify the program to have a second menu for choosing line styles and get it to run.


## [Review 1](review/01.txt)
Why would you want a graphical user interface?

## [Review 2](review/02.txt)
When would you want a non-graphical user interface?

## [Review 3](review/03.txt)
What is a software layer?

## [Review 4](review/04.txt)
Why would you want to layer software?

## [Review 5](review/05.txt)
What is a callback?

## [Review 6](review/06.txt)
What is a widget?

## [Review 7](review/07.txt)
Is Qt an acronym?

## [Review 8](review/08.txt)
How do you pronounce Qt?

## [Review 9](review/09.txt)
What other GUI toolkits have you heard of?

## [Review 10](review/10.txt)
Which systems use the term _widget_ and which prefer _control_?

## [Review 11](review/11.txt)
What are examples of widgets?

## [Review 12](review/12.txt)
When would you use an inbox?

## [Review 13](review/13.txt)
What is the type of the value stored in an inbox?

## [Review 14](review/14.txt)
When would you use a button?

## [Review 15](review/15.txt)
When would you use a menu?

## [Review 16](review/16.txt)
What is control inversion?

## [Review 17](review/17.txt)
What is the basic strategy for debugging a GUI program?

## [Review 18](review/18.txt)
Why is debugging a GUI program harder than debugging an "ordinary program using streams for I/O"?

## [Review 19](review/19.txt)
How do you animate a widget?


## [Exercise 1](exercises/01/main.cpp)
Make a `My_window` that's a bit like `Simple_window` except that it has two buttons, `next` and `quit`.

## [Exercise 2](exercises/02/main.cpp)
Make a window (based on `My_window`) with a 4-by-4 checkerboard of square buttons.
When pressed, a button performs a simple action, such as printing its coordinates in an output box, or turns a slightly different color (until another button is pressed).
