#include "PPP/Simple_window.h"
#include "PPP/Graph.h"

double dsin(double d) { return sin(d); }

int main(int /*argc*/, char * /*argv*/[])
{
    using namespace Graph_lib;

    // Window size
    constexpr int win_width = 600;
    constexpr int win_height = 400;

    Application app;
    Point top_left{600, 400};

    // Our window
    Simple_window win{top_left, win_width, win_height, "My window"};

    // Create a horizontal and a vertical axis
    Axis xa{Axis::x, Point{50, 300}, 500, 20, "x axis"};
    Axis ya{Axis::y, Point{50, 300}, 250, 10, "y axis"};

    // Create a sine function to plot
    Function sine{dsin, 0, 100, Point{50,175}, 1000, 25, 100};
    sine.set_color(Color::red);

    // Set the vertical axis' and its label's color
    ya.set_color(Color::cyan);
    ya.label.set_color(Color::dark_red);

    // Add the objects to the window
    win.attach(xa);
    win.attach(ya);
    win.attach(sine);

    // Change the window frame label
    win.set_label("Sine");

    // To keep window on screen
    win.wait_for_button();
}
