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
    constexpr int win_width = 800;
    constexpr int win_height = 600;

    // Create window
    const std::string label = "Shape that doesn't fit its window";
    Simple_window win{Point{win_x, win_y}, win_width, win_height, label};

    // Rectangle size
    constexpr double scale = 2;
    constexpr int rect_width = win_width * scale;
    constexpr int rect_height = win_height * scale;

    // Center rectangle
    constexpr int rect_x = (win_width - rect_width) / 2;
    constexpr int rect_y = (win_height - rect_height) / 2;

    // Create rectangle filled yellow, lines of dark blue
    Rectangle rect{Point{rect_x, rect_y}, rect_width, rect_height};
    rect.set_fill_color(Color::yellow);
    rect.set_color(Color::dark_blue);

    win.attach(rect);
    win.wait_for_button();
}
