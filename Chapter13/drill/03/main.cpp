#include "PPP/Simple_window.h"
#include "PPP/Graph.h"

int main(int /*argc*/, char * /*argv*/[])
{
    // Make Graph_lib's contents available implicitly without using its scope
    using namespace Graph_lib;

    // Initialize display engine
    Application app;

    // [1] Create window
    constexpr int win_x = 200;
    constexpr int win_y = 100;
    constexpr int win_width = 600;
    constexpr int win_height = 600;
    const std::string label = "Function graphs";
    Simple_window win{Point{win_x, win_y}, win_width, win_height, label};

    // [2] x and y axis
    constexpr int xa_length = 400;
    constexpr int ya_length = 400;
    constexpr int notch_spacing = 20;
    const std::string axis_label = "1 == 20 pixels";
    const Point win_center{win_width / 2, win_height / 2};
    const Point xa_p{win_center.x - xa_length / 2, win_center.y};
    const Point ya_p{win_center.x, win_center.y + ya_length / 2};
    Axis xa{Axis::x, xa_p, xa_length, notch_spacing, axis_label};
    Axis ya{Axis::y, ya_p, ya_length, notch_spacing, axis_label};
    win.attach(xa);
    win.attach(ya);

    // [3] red axes
    const Color axis_color{Color::red};
    xa.set_color(axis_color);
    ya.set_color(axis_color);

    win.wait_for_button();
}
