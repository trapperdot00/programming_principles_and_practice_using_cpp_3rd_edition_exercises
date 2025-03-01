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
