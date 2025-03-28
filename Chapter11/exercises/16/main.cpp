#include "PPP/Simple_window.h"
#include "PPP/Graph.h"

struct Poly : public Polygon {
    Poly() {}
    // Don't reinvent the wheel:
    // reuse already existing code
    // that checks for intersecting lines
    Poly(std::initializer_list<Point> points) {
        for (const Point& p : points)
            Polygon::add(p);
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
    constexpr int win_width = 400;
    constexpr int win_height = 400;
    const std::string label = "Poly";
    Simple_window win{Point{win_x, win_y}, win_width, win_height, label};

    Point p1{win_width / 10, win_height / 2};
    Point p2{win_width / 2, 9 * win_height / 10};
    Point p3{9 * win_width / 10, win_height / 2};
    Point p4{win_width / 2, win_height / 10};
    Poly poly1{p1, p2, p3, p4};
    poly1.set_fill_color(Color::yellow);
    win.attach(poly1);

    Point p5{0, 0};
    Point p6{win_width, 0};
    Point p7{win_width / 2, win_height / 2};
    Poly poly2{p5, p6, p7};
    poly2.set_fill_color(Color::dark_cyan);
    win.attach(poly2);

    Point p8{win_width, win_height};
    Point p9{0, win_height};
    Point p10{win_width / 2, win_height / 2};
    Poly poly3{p8, p9, p10};
    poly3.set_fill_color(Color::dark_green);
    win.attach(poly3);

    win.wait_for_button();
}
