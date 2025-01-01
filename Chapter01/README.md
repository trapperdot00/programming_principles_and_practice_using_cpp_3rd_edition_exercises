# 1: Hello, World!

- [Drill](#drill)
- [Review](#review)
- [Terms](terms.txt)
- [Exercises](#exercises)

# Drill

## Drill 1
Figure out how to compile and run a program on your machine. This may be a good time to get a bit of help from someone who has done that before.

## Drill 2
If you use an IDE, set up an empty console C++ project called `hello_world`. Otherwise, if you plan to use the command line, get a command window, figure out how to use an editor to type in your code, and see §0.3.1.

## [Drill 3](drill/03/01.cpp)
Type in `hello_world.cpp`, exactly as specified below, save it in your practice directory (folder), and include it in your `hello_world` project.
```
import std;
int main()  // C++ programs start by executing the function main
{
    std::cout << "Hello, World!\n"; // output "Hello, World!"
}
```
What if you don’t have an up-to-date C++ implementation that supports module std? Then, use a less elegant and less efficient technique that has worked since the early days of C: #include a header file as is explained in §7.7.2:
```
#include<iostream>
int main()  // C++ programs start by executing the function main
{
    std::cout << "Hello, World!\n"; // output "Hello, World!"
}
```

## Drill 4
Compile and run the “Hello, World!” program. An IDE will have a compile-and-run button. Even something as simple as “Hello, World!” very rarely compiles and runs in a first attempt to use a new programming language or a new programming environment.

Find the problem and fix it! This is a point where asking for help from a more experienced person is sensible, but be sure to understand what you are shown so that you can do it all by yourself before proceeding further.

## [Drill 5](drill/05)
By now, you have probably encountered some errors and had to correct them. Now is the time to get a bit better acquainted with your compiler’s error-detection and error-reporting facilities! Try the eight programs from §1.3 to see how your programming environment reacts. Think of at least five more errors you might have made typing in your program (e.g., leave the Caps Lock key on while typing a word, or type a comma instead of a semicolon) and try each to see what happens when you try to compile and run those versions.

# Review

## [Review 1](review/01.txt)
What is the purpose of the “Hello, World!” program?

## [Review 2](review/02.txt)
Name the four parts of a function.

## [Review 3](review/03.txt)
Name a function that must appear in every C++ program.

## [Review 4](review/04.txt)
In the “Hello, World!” program, what is the purpose of the line `return 0;`?

## [Review 5](review/05.txt)
What is the purpose of the compiler?

## [Review 6](review/06.txt)
What is the purpose of the `import` statement?

## [Review 7](review/07.txt)
What is the purpose of the `#include` directive?

## [Review 8](review/08.txt)
What does a `.cpp` suffix at the end of a file name signify in C++?

## [Review 9](review/09.txt)
What does the linker do for your program?

## [Review 10](review/10.txt)
What is the difference between a source file and an object file?

## [Review 11](review/11.txt)
What is an executable?

## [Review 12](review/12.txt)
What is an IDE and what does it do for you?

## [Review 13](review/13.txt)
How do you get a compiled program to run?

## [Review 14](review/14.txt)
What is a comment?

## [Review 15](review/15.txt)
What is the purpose of a drill?

## [Review 16](review/16.txt)
If you understand everything in the textbook, why is it necessary to practice?

# Exercises

## [Exercise 1](exercises/01/01.cpp)
Change the program to output the two lines
```
Hello, programming!
Here we go!
```

## [Exercise 2](exercises/02/01.cpp)
Expanding on what you have learned, write a program that lists the instructions for a computer to find the upstairs bathroom, discussed in §1.1. Can you think of any more steps that a person would assume, but that a computer would not? Add them to your list. This is a good start in“thinking like a computer.” Warning: For most people, “go to the bathroom” is a perfectly adequate instruction. For someone with no experience with houses or bathrooms (imagine a stone-age person, somehow transported into your dining room) the list of necessary instructions could be very long. Please don’t use more than a page. For the benefit of the reader, you may add a short description of the layout of the house you are imagining.

## [Exercise 3](exercises/03/01.cpp)
Write a description of how to get from the front door of your dorm room, apartment, house, whatever, to the door of your classroom (assuming you are attending some school; if you are not, pick another target). Have a friend try to follow the instructions and annotate them with improvements as he or she goes along. To keep friends, it may be a good idea to “field test” those instructions yourself before giving them to a friend.

## Exercise 4
Find a good cookbook. Read the instructions for baking blueberry muffins (if you are in a country where “blueberry muffins” is a strange, exotic dish, use a more familiar dish instead). Please note that with a bit of help and instruction, most of the people in the world can bake delicious blueberry muffins. It is not considered advanced or difficult fine cooking. However, for the author, few exercises in this book are as difficult as this one. It is amazing what you can do with a bit of practice.

- Rewrite those instructions so that each individual action is in its own numbered paragraph. Be careful to list all ingredients and all kitchen utensils used at each step. Be careful about crucial details, such as the desired oven temperature, preheating the oven, the preparation of the muffin pan, the way to time the cooking, and the need to protect your hands when removing the muffins from the oven.

- Consider those instructions from the point of view of a cooking novice (if you are not one, get help from a friend who does not know how to cook). Fill in the steps that the book’s author (almost certainly an experienced cook) left out for being obvious.

- Build a glossary of terms used. (What’s a muffin pan? What does preheating do? What do you mean by “oven”?)

- Now bake some muffins and enjoy your results.

## Exercise 5
Write a definition for each of the terms from “Terms.” First try to see if you can do it without looking at the chapter (not likely), then look through the chapter to find definitions. You might find the difference between your first attempt and the book’s version interesting. You might consult some suitable online glossary, such as `www.stroustrup.com/glossary.html`. By writing your own definition before looking it up, you reinforce the learning you achieved through your reading. If you have to reread a section to form a definition, that just helps you to understand. Feel free to use your own words for the definitions and make the definitions as detailed as you think reasonable. Often, an example after the main definition will be helpful. You may like to store the definitions in a file so that you can add to them from the “Terms” sections of later chapters.
