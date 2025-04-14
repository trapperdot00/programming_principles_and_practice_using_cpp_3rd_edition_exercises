#include "PPP/Simple_window.h"
#include "PPP/Graph.h"

int main(int /*argc*/, char * /*argv*/[])
{
    // Make Graph_lib's contents available implicitly without using its scope
    using namespace Graph_lib;

    // Initialize display engine
    Application app;

    // Create window
    constexpr int win_x = 200;
    constexpr int win_y = 100;
    constexpr int win_width = 600;
    constexpr int win_height = 600;
    const std::string label = "Function graphs";
    Simple_window win{Point{win_x, win_y}, win_width, win_height, label};

    win.wait_for_button();
}
