#include "PPP/Simple_window.h"
#include "PPP/Graph.h"

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
    Axis xa{Axis::x, Point{20, 300}, 280, 10, "x axis"};
    Axis ya{Axis::y, Point{20, 300}, 280, 10, "y axis"};

    // Set the vertical axis' and its label's color
    ya.set_color(Color::cyan);
    ya.label.set_color(Color::dark_red);

    // Add the axes to the window
    win.attach(xa);
    win.attach(ya);

    // Change the window frame label
    win.set_label("Y axis");

    // To keep window on screen
    win.wait_for_button();
}
