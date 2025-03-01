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
    constexpr int win_width = 800;
    constexpr int win_height = 1000;
    const std::string label = "8-by-8 grid";
    Simple_window win{Point{win_x, win_y}, win_width, win_height, label};

    constexpr int grid_cols = 8;
    constexpr int grid_rows = 8;
    constexpr int grid_width = 800;
    constexpr int grid_height = 800;
    constexpr int grid_col_width = grid_width / grid_cols;
    constexpr int grid_row_height = grid_height / grid_rows;
    Lines grid;
    for (int x = grid_col_width; x <= grid_width; x += grid_col_width) {
        grid.add(Point{x, 0}, Point{x, grid_height});
        std::cout << x << ';' << 0 << '\t' << x << ';' << grid_height << '\n';
    }
    for (int y = grid_row_height; y <= grid_height; y += grid_row_height) {
        grid.add(Point{0, y}, Point{grid_width, y});
        std::cout << 0 << ';' << y << '\t' << grid_width << ';' << y << '\n';
    }
    win.attach(grid);
    win.wait_for_button();
}
