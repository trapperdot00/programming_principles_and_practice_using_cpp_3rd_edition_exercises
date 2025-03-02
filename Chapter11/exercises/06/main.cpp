#include "PPP/Simple_window.h"
#include "PPP/Graph.h"

// Inherit from Closed_polyline, we are sure that
// there will be no intersecting lines
struct Regular_hexagon : public Closed_polyline {
    Regular_hexagon(const Point& center, int distance) {
        // Whole circle: 360°
        constexpr double full_circle = 2 * M_PI;
        // Start at the top (90° angle)
        double angle = 0.5 * M_PI;
        // Increment by 60° each step
        double step = full_circle / 6;
        for (int i = 0; i < 6; ++i, angle += step) {
            // Basic trigonometry, get offsets from center
            int delta_x = distance * std::cos(angle);
            int delta_y = distance * std::sin(angle);
            // Get absolute coordinates
            int x = center.x + delta_x;
            int y = center.y + delta_y;
            Point p{x, y};
            Closed_polyline::add(p);
        }
    }
};

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
    constexpr int win_height = 600;
    const std::string label = "Regular_hexagon";
    Simple_window win{Point{win_x, win_y}, win_width, win_height, label};

    Vector_ref<Regular_hexagon> vec;
    for (int i = 0; i < 7; ++i) {
        // Hexagon distance from center to corner point
        constexpr int distance = 100;
        // Distance ratio from vertical screen edges, range: [0,1]
        constexpr double vertical_edge = 0.2;
        double current_edge = i % 2 ? 0 + vertical_edge : 1 - vertical_edge;
        int x = i * 100 + distance;
        // One up, one down pattern
        int y = win_height * current_edge;
        Point p{x, y};
        vec.push_back(std::make_unique<Regular_hexagon>(p, distance));
        vec[vec.size()-1].set_fill_color(Color::dark_cyan);
    }

    for (Regular_hexagon* p : vec)
        win.attach(*p);

    win.wait_for_button();
}
