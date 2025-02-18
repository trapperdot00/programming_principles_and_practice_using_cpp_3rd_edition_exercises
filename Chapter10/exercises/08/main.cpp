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
    const std::string label = "Olympic five rings";
    Simple_window win{Point{win_x, win_y}, win_width, win_height, label};

    constexpr double scale = 1;
    constexpr int x_offset = 0;
    constexpr int y_offset = 0;

    constexpr int radius = 100 * scale;
    constexpr int distance = radius * scale * 1.15;

    constexpr int line_thickness = 18;
    Line_style circle_style{Line_style::solid, line_thickness};

    Point black_center{win_width / 2 + x_offset, win_height / 2 - distance / 2 + y_offset};
    Point yellow_center{black_center.x - distance, black_center.y + distance};
    Point blue_center{yellow_center.x - distance, yellow_center.y - distance};
    Point green_center{black_center.x + distance, black_center.y + distance};
    Point red_center{green_center.x + distance, green_center.y - distance};

    Circle black{black_center, radius};
    black.set_style(circle_style);

    Circle yellow{yellow_center, radius};
    yellow.set_color(Color{252, 177, 49});
    yellow.set_style(circle_style);

    Circle blue{blue_center, radius};
    blue.set_color(Color{0, 129, 200});
    blue.set_style(circle_style);

    Circle green{green_center, radius};
    green.set_color(Color{0, 116, 81});
    green.set_style(circle_style);

    Circle red{red_center, radius};
    red.set_color(Color{238, 51, 78});
    red.set_style(circle_style);

    win.attach(blue);
    win.attach(yellow);
    win.attach(black);
    win.attach(green);
    win.attach(red);

    win.wait_for_button();
}
