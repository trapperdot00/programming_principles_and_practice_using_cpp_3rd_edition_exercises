#include "PPP/Simple_window.h"
#include "PPP/Graph.h"

int main(int /*argc*/, char * /*argv*/[])
{
    // Make Graph_lib's contents available implicitly without using its scope
    using namespace Graph_lib;

    // Initialize display engine
    Application app;

    // Window top-left point
    constexpr int win_x = 600;
    constexpr int win_y = 400;

    // Window size
    constexpr int win_width = 452;
    constexpr int win_height = 315;

    // Create window
    const std::string win_title = "Howdy";
    Simple_window win{Point{win_x, win_y}, win_width, win_height, win_title};

    // Rectangle size
    constexpr int rect_width = 100;
    constexpr int rect_height = 30;

    // Center rectangle
    constexpr int rect_x = (win_width - rect_width) / 2;
    constexpr int rect_y = (win_height - rect_height) / 2;

    // Create rectangle with "Howdy!" inside it
    Rectangle rect{Point{rect_x, rect_y}, rect_width, rect_height};
    Text text{Point{rect_x, rect_y}, "Howdy!"};

    // Paint our objects onto the window
    win.attach(rect);
    win.attach(text);

    // Don't exit immediately
    win.wait_for_button();
}
