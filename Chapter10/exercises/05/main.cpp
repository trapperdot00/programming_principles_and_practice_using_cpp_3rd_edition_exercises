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

    // Create window
    const std::string label = "Framed rectangle";
    Simple_window win{Point{win_x, win_y}, x_max(), y_max(), label};

    // Width is two thirds, height is three quarters of the screen
    const int rect_width = x_max() * 2 / 3;
    const int rect_height = y_max() * 3 / 4;

    // Center rectangle
    const int rect_x = (x_max() - rect_width) / 2;
    const int rect_y = (y_max() - rect_height) / 2;

    // Create cyan rectangle
    Rectangle rect{Point{rect_x, rect_y}, rect_width, rect_height};
    rect.set_fill_color(Color::cyan);

    // Pixel-per-inch of my monitor (2560x1440 27")
    constexpr double monitor_ppi = 108.79;

    // Distance from frame and rectangle: 1/4 inch
    constexpr int distance = monitor_ppi / 4;

    // Add distance on both sides
    const int frame_width = rect_width + distance * 2;
    const int frame_height = rect_height + distance * 2;

    // Center frame
    const int frame_x = (x_max() - frame_width) / 2;
    const int frame_y = (y_max() - frame_height) / 2;

    // Create red frame
    Rectangle frame{Point{frame_x, frame_y}, frame_width, frame_height};
    frame.set_color(Color::red);

    // Paint to window
    win.attach(rect);
    win.attach(frame);

    win.wait_for_button();
}
