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
    constexpr int win_width = 100000;
    constexpr int win_height = 100000;

    // Create window
    const std::string label = "Oversized window";
    Simple_window win{Point{win_x, win_y}, win_width, win_height, label};

    // On a Linux machine with Wayland, the oversized window is fullscreened

    win.wait_for_button();
}
