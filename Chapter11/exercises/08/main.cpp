#include "PPP/Simple_window.h"
#include "PPP/Graph.h"

struct Regular_polygon : public Closed_polyline {
    Regular_polygon(const Point& center, int sides, double distance) {
        if (sides < 3)
            throw std::runtime_error{"Regular_polygon must have at least 3 sides"};
        constexpr double full_circle = 2 * M_PI;
        const double angle_step = full_circle / sides;
        // Odd sided polygons have one of their points on the top-center,
        // Even sided polygons have one of their side's center on the top-center
        double angle = 0.5 * M_PI + (sides % 2 ? 0 : full_circle / (2 * sides));
        for (int i = 0; i < sides; ++i) {
            int dx = distance * std::cos(angle);
            int dy = distance * std::sin(angle);
            int x = center.x + dx;
            int y = center.y - dy;
            Point p{x, y};
            Closed_polyline::add(p);
            angle += angle_step;
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
    const std::string label = "Regular_polygon";
    Simple_window win{Point{win_x, win_y}, win_width, win_height, label};

    Vector_ref<Regular_polygon> vec;
    constexpr int width = 4;
    constexpr int height = 4;
    constexpr int field_width = win_width / width;
    constexpr int field_height = win_height / height;
    constexpr double distance = field_width / 2 * 0.75;
    int x = field_width / 2;
    int y = field_height / 2;
    int side_count = 3;
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            Point p{x, y};
            vec.push_back(std::make_unique<Regular_polygon>(p, side_count, distance));
            x += field_width;
            ++side_count;
        }
        x = field_width / 2;
        y += field_height;
    }
    const std::array<Color, 10> colors = {
        Color::cyan, Color::dark_cyan, Color::dark_green,
        Color::green, Color::yellow, Color::dark_yellow,
        Color::black, Color::magenta, Color::red,
        Color::blue
    };
    int i = 0;
    for (Regular_polygon* p : vec) {
        p->set_fill_color(colors[i++ % colors.size()]);
        win.attach(*p);
    }

    win.wait_for_button();
}
