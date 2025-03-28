#include "PPP/Simple_window.h"
#include "PPP/Graph.h"

struct Star : public Polygon {
    Star(Point center, int point_count, int outer_radius, int inner_radius)
    {
        if (point_count < 3)
            throw std::runtime_error{"invalid number of star points"};
        if (outer_radius <= inner_radius)
            throw std::runtime_error{"outer radius smaller than or equal to inner radius"};
        // Start rotation at the top of the circle going counter-clockwise
        // alternating between the outer and inner circle calculating
        // the current angle's intersection with the circle as the next point
        double angle = M_PI / 2;
        double step = M_PI / point_count;
        for (int i = 0; i < point_count * 2; ++i, angle += step) {
            int radius = (i % 2 == 0) ? outer_radius : inner_radius;
            int x = radius * std::cos(angle);
            int y = radius * std::sin(angle);
            Point p{center.x + x, center.y - y};
            Polygon::add(p);
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
    const std::string label = "Star";
    Simple_window win{Point{win_x, win_y}, win_width, win_height, label};

    Star s1{Point{win_width / 2, win_height / 2}, 5, 100, 35};
    s1.set_fill_color(Color::yellow);
    s1.set_style(Line_style{Line_style::dot, 5});
    win.attach(s1);

    Star s2{Point{0, 0}, 10, 200, 50};
    s2.set_fill_color(Color::blue);
    win.attach(s2);

    Star s3{Point{win_width / 2, int(1.2 * win_height)}, 50, 300, 200};
    s3.set_fill_color(Color::green);
    s3.set_style(Line_style{Line_style::dashdotdot, 10});
    s3.set_color(Color::dark_green);
    win.attach(s3);

    Star s4{Point{int(0.8 * win_width), int(0.3 * win_height)}, 6, 150, 40};
    s4.set_fill_color(Color::magenta);
    win.attach(s4);

    Star s5{Point{win_width / 5, win_height / 2}, 7, 150, 50};
    s5.set_fill_color(Color::black);
    s5.set_color(Color::red);
    s5.set_style(Line_style{Line_style::dashdot, 10});
    win.attach(s5);

    win.wait_for_button();
}
