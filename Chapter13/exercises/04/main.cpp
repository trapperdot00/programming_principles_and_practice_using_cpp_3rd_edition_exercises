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
    constexpr int win_height = 600;
    const std::string label = "sin, cos, sin+cos, sin*sin+cos*cos";

    Simple_window win{Point{win_x, win_y}, win_width, win_height, label};

    constexpr int xa_offset = 31;
    constexpr int xa_spacing = 31;

    constexpr int ya_offset = 20;
    constexpr int ya_spacing = 20;

    constexpr int xa_length = win_width - xa_offset - xa_spacing;
    constexpr int ya_length = win_height - ya_offset - ya_spacing;

    constexpr Point xa_p{xa_offset, win_height / 2};
    constexpr Point ya_p{win_width / 2, win_height - ya_offset};

    constexpr int x_scale = 50;
    constexpr int y_scale = 50;

    Axis xa{Axis::x, xa_p, xa_length, xa_length / x_scale, "x (1 notch == 1)"};
    Axis ya{Axis::y, ya_p, ya_length, ya_length / y_scale, "y (1 notch == 1)"};
    win.attach(xa);
    win.attach(ya);

    constexpr int r1 = xa_length / x_scale / -2;
    constexpr int r2 = -r1;

    constexpr int x_orig = win_width / 2;
    constexpr int y_orig = win_height / 2;
    constexpr Point orig{x_orig, y_orig};
    constexpr int pcount = 25000;

    Function f1([](double d) { return std::sin(d); }, r1, r2, orig, pcount, x_scale, y_scale);
    f1.set_color(Color::red);
    win.attach(f1);
    Text t1{Point{235, 275}, "sine"};
    t1.set_color(Color::red);
    win.attach(t1);

    Function f2([](double d) { return std::cos(d); }, r1, r2, orig, pcount, x_scale, y_scale);
    f2.set_color(Color::blue);
    win.attach(f2);
    Text t2{Point{115, 320}, "cosine"};
    t2.set_color(Color::blue);
    win.attach(t2);

    Function f3([](double d) { return std::sin(d) + std::cos(d); }, r1, r2, orig, pcount, x_scale, y_scale);
    f3.set_color(Color::green);
    win.attach(f3);
    Text t3{Point{220, 375}, "sine+cosine"};
    t3.set_color(Color::green);
    win.attach(t3);

    Function f4([](double d) { return std::pow(std::sin(d), 2) + std::pow(std::cos(d), 2); }, r1, r2, orig, pcount, x_scale, y_scale);
    f4.set_color(Color::dark_magenta);
    win.attach(f4);
    Text t4{Point{550, 230}, "sin^2+cos^2"};
    t4.set_color(Color::dark_magenta);
    win.attach(t4);

    win.wait_for_button();
    win.close();
}
