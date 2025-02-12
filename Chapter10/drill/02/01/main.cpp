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

    // Create a horizontal axis
    Axis xa{Axis::x, Point{20, 300}, 280, 10, "x axis"};

    // Add the horizontal axis to the window
    win.attach(xa);

    // Change the window frame label
    win.set_label("X axis");

    // To keep window on screen
    win.wait_for_button();
}
