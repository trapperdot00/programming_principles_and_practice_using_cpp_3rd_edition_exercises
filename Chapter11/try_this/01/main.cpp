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
    const std::string label = "Grid with style";
    Simple_window win{Point{win_x, win_y}, x_max(), y_max(), label};

    // Grid size
    constexpr int grid_width = 80;
    constexpr int grid_height = 40;

    Lines grid;
    // Add vertical lines
    for (int x = grid_width; x < x_max(); x += grid_width)
        grid.add(Point{x, 0}, Point{x, y_max()});
    // Add horizontal lines
    for (int y = grid_height; y < y_max(); y += grid_height)
        grid.add(Point{0, y}, Point{x_max(), y});

    // Stylize
    grid.set_color(Color::blue);
    grid.set_style(Line_style{Line_style::dashdotdot, 3});

    win.attach(grid);
    win.wait_for_button();
}
