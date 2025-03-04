#include "PPP/Simple_window.h"
#include "PPP/Graph.h"

// Useful for avoiding repeated code: returns value of both signs
template <typename T>
std::pair<T, T> plus_minus(const T& t) {
    return std::make_pair(t, -t);
}

// Get the intersection points between a vertical line and an ellipse from the equation
// y = sqrt(b^2 - (b^2*x^2)/a^2)
std::pair<Point, Point> vertical_intersection(const Point& center, int width, int height, int x) {
    // X from center
    int relative_x = center.x - x;
    if (relative_x >= width / 2 || relative_x <= -width / 2)
        throw std::runtime_error{"less than two intersections"};
    // Avoid recalculating reused values, and add names for subexpressions
    const double a_squared = std::pow(width / 2, 2);
    const double b_squared = std::pow(height / 2, 2);
    const double x_squared = std::pow(relative_x, 2);
    // Relative heights where intersection happens
    const auto [dy1, dy2] = plus_minus(std::sqrt(b_squared - b_squared*x_squared / a_squared));
    // Convert to absolute height values
    const int y1 = center.y - dy1;
    const int y2 = center.y - dy2;
    // Construct absolute coordinates
    const Point p1{x, y1};
    const Point p2{x, y2};
    return std::make_pair(p1, p2);
}

int main(int /*argc*/, char * /*argv*/[])
{
    // Make Graph_lib's contents available implicitly without using its scope
    using namespace Graph_lib;
    // Initialize display engine
    Application app;
    // Create window
    constexpr int win_x = 200;
    constexpr int win_y = 100;
    constexpr int win_width = 500;
    constexpr int win_height = 500;
    const std::string label = "Ellipse, foci, and lines";
    Simple_window win{Point{win_x, win_y}, win_width, win_height, label};

    constexpr int ellipse_width = 300;
    constexpr int ellipse_height = 200;
    const Point center{win_width / 2, win_height / 2};
    Ellipse ellipse{center, ellipse_width / 2, ellipse_height / 2};

    constexpr int axis_gap = 20;

    constexpr int x_axis_length = 400;
    constexpr int xa_notches = x_axis_length / axis_gap;
    const Point xa_center{center.x - x_axis_length / 2, center.y};
    Axis xa(Axis::x, xa_center, x_axis_length, xa_notches, "");

    constexpr int y_axis_length = 300;
    constexpr int ya_notches = y_axis_length / axis_gap;
    const Point ya_center{center.x, center.y + y_axis_length / 2};
    Axis ya(Axis::y, ya_center, y_axis_length, ya_notches, "");

    Mark focus1{ellipse.focus1(), 'x'};
    Mark focus2{ellipse.focus2(), 'x'};

    // Vertical line to look for intersection at with ellipse
    constexpr int x = 340;
    const Point intersection = vertical_intersection(center, ellipse_width, ellipse_height, x).first;
    // Mark upper intersection
    Mark m{intersection, 'x'};

    // Connect intersection and foci
    Line line1{ellipse.focus1(), intersection};
    Line line2{ellipse.focus2(), intersection};

    win.attach(ellipse);
    win.attach(xa);
    win.attach(ya);
    win.attach(focus1);
    win.attach(focus2);
    win.attach(m);
    win.attach(line1);
    win.attach(line2);

    win.wait_for_button();
}
