#include "PPP/Simple_window.h"
#include "PPP/Graph.h"

double one(double) {
    return 1;
}

double slope(double x) {
    return 0.5 * x;
}

double square(double x) {
    return x * x;
}

int main(int /*argc*/, char * /*argv*/[])
{
    // Make Graph_lib's contents available implicitly without using its scope
    using namespace Graph_lib;

    // Initialize display engine
    Application app;

    // [1] Create window
    constexpr int win_x = 200;
    constexpr int win_y = 100;
    constexpr int win_width = 600;
    constexpr int win_height = 600;
    const std::string label = "Function graphs";
    Simple_window win{Point{win_x, win_y}, win_width, win_height, label};

    // [2] x and y axis
    constexpr int xa_length = 400;
    constexpr int ya_length = 400;
    constexpr int notch_spacing = 20;
    const std::string axis_label = "1 == 20 pixels";
    const Point win_center{win_width / 2, win_height / 2};
    const Point xa_p{win_center.x - xa_length / 2, win_center.y};
    const Point ya_p{win_center.x, win_center.y + ya_length / 2};
    Axis xa{Axis::x, xa_p, xa_length, notch_spacing, axis_label};
    Axis ya{Axis::y, ya_p, ya_length, notch_spacing, axis_label};
    win.attach(xa);
    win.attach(ya);

    // [3] red axes
    const Color axis_color{Color::red};
    xa.set_color(axis_color);
    ya.set_color(axis_color);

    // [4] f(x) = 1
    // [5] scale = 20
    // [6] symbolic constants for range, precision, scale
    constexpr int range_begin = -10;
    constexpr int range_end = 11;
    constexpr int f_precision = 400;
    constexpr int x_scale = notch_spacing;
    constexpr int y_scale = notch_spacing;
    Function one_f{one, range_begin, range_end, win_center, f_precision, x_scale, y_scale};
    win.attach(one_f);

    // [7] g(x) = 0.5x
    Function slope_f(slope, range_begin, range_end, win_center, f_precision, x_scale, y_scale);
    win.attach(slope_f);

    // [8] slope label
    Point slope_fp1{slope_f.point(0)};
    Text slope_l{Point{slope_fp1.x, slope_fp1.y - 20}, "0.5x"};
    win.attach(slope_l);

    // [9] h(x) = x^2
    Function square_f{square, range_begin, range_end, win_center, f_precision, x_scale, y_scale};
    win.attach(square_f);

    // [10] i(x) = cos(x)
    Function cos_f{[](double x){ return std::cos(x); },
                   range_begin, range_end, win_center, f_precision, x_scale, y_scale};
    win.attach(cos_f);

    win.wait_for_button();
    win.close();
}
