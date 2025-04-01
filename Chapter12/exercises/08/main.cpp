#include "PPP/Simple_window.h"
#include "PPP/Graph.h"

class Octagon : public Closed_polyline {
public:
    Octagon(Point center, int r) {
        constexpr int sides = 8;
        constexpr double full_circle = 2 * M_PI;
        constexpr double angle_step = full_circle / sides;
        for (double angle = angle_step / 2; angle < full_circle; angle += angle_step) {
            int dx = r * std::cos(angle);
            int dy = r * std::sin(angle);
            int x = center.x + dx;
            int y = center.y + dy;
            Closed_polyline::add(Point{x, y});
        }
    }
    void test() const {
        std::cout << "Octagon!\n";
    }
};

void test_shape(Shape& sh) {
    sh.set_color(Color::red);
    sh.set_fill_color(Color::black);
    sh.set_style(Line_style{Line_style::dash, 5});
    std::cout << "Shape color: "
              << sh.color().as_int()
              << "\nShape fill color: "
              << sh.fill_color().as_int()
              << "\nShape style: "
              << sh.style().style()
              << "\nShape number of points: "
              << sh.number_of_points()
              << "\nShape points:\n";
    for (int i = 0; i < sh.number_of_points(); ++i) {
        Point p = sh.point(i);
        std::cout << '(' << p.x << ';' << p.y << ")\n";
    }
    sh.move(100, 0);

    // protected
    // sh.add(Point{10, 10});
    // sh.redraw();

    // deleted
    // sh = Rectangle{Point{10, 10}, 10, 10};

    // Shape doesn't know about this member,
    // not in its interface
    // sh.test();
}

void test_octagon(Octagon& oc) {
    oc.set_color(Color::blue);
    oc.set_fill_color(Color::cyan);
    oc.set_style(Line_style{Line_style::solid, 10});
    std::cout << "\nOctagon color: "
              << oc.color().as_int()
              << "\nOctagon fill color: "
              << oc.fill_color().as_int()
              << "\nOctagon style: "
              << oc.style().style()
              << "\nOctagon number of points: "
              << oc.number_of_points()
              << "\nOctagon points:\n";
    for (int i = 0; i < oc.number_of_points(); ++i) {
        Point p = oc.point(i);
        std::cout << '(' << p.x << ';' << p.y << ")\n";
    }
    oc.move(-200, 0);
    oc.test();

    // protected
    // oc.add(Point{10, 10});
    // oc.redraw();

    // deleted
    // oc = Rectangle{Point{10, 10}, 10, 10};
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
    const std::string label = "Octagon test";
    Simple_window win{Point{win_x, win_y}, win_width, win_height, label};

    // Coordinates and step
    constexpr int center_x = win_width / 2;
    constexpr int center_y = win_height / 2;
    constexpr int x_step = win_width / 5;
    constexpr int y_step = win_height / 5;

    Octagon oc{Point{center_x, center_y}, std::min(x_step, y_step)};
    win.attach(oc);

    test_shape(oc);
    win.wait_for_button();

    test_octagon(oc);
    win.wait_for_button();
}
