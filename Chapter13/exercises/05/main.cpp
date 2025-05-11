#include "PPP/Simple_window.h"
#include "PPP/Graph.h"

double term(int n) {
    return double(1) / (1 + n * 2);
}

double leibniz(int n) {
    double d = 0;
    for (int i = 0; i < n; ++i) {
        double t = term(i);
        if (i % 2 == 0)
            d += t;
        else
            d -= t;
    }
    return d;
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
    constexpr int win_width = 800;
    constexpr int win_height = 600;
    const std::string label = "Leibniz's series approximation";

    Simple_window win{Point{win_x, win_y}, win_width, win_height, label};

    constexpr int x_offset = 100;
    constexpr int x_spacing = 100;
    constexpr int xa_length = win_width - x_offset - x_spacing;
    constexpr int x_scale = 60;
    constexpr Point xa_p{x_spacing, win_height / 2};

    constexpr int y_offset = 40;
    constexpr int y_spacing = 40;
    constexpr int ya_length = win_height - y_offset - y_spacing;
    constexpr int y_scale = 120;
    constexpr Point ya_p{x_offset, win_height - y_offset};

    Axis xa{Axis::x, xa_p, xa_length, xa_length / x_scale};
    win.attach(xa);

    Axis ya{Axis::y, ya_p, ya_length, ya_length / y_scale};
    win.attach(ya);

    for (int i = 1; i < 51; ++i) {
        double value = leibniz(i);
        std::ostringstream os;
        os << "Precision: " << i << "; value: " << value << ", times four: " << 4 * value;
        Text t{Point{20, 20}, os.str()};
        Function f([value](double) { return value; }, 0, xa_length / x_scale, Point{x_offset, win_height / 2}, 10, x_scale, y_scale);
        f.set_color(Color::blue);
        win.attach(t);
        win.attach(f);
        win.wait_for_button();
        win.detach(t);
        win.detach(f);
    }
    win.close();
}
