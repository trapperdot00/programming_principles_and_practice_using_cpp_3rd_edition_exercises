#include "PPP/Simple_window.h"
#include "PPP/Graph.h"

class Box : public Polygon {
public:
    Box(Point tl, int w, int h, int r)
    :   Polygon {
            Point{tl.x + r, tl.y + r},
            Point{tl.x, tl.y + r},
            Point{tl.x, tl.y + h - r},
            Point{tl.x + r, tl.y + h - r},
            Point{tl.x + r, tl.y + h},
            Point{tl.x + w - r, tl.y + h},
            Point{tl.x + w - r, tl.y + h - r},
            Point{tl.x + w, tl.y + h - r},
            Point{tl.x + w, tl.y + r},
            Point{tl.x + w - r, tl.y + r},
            Point{tl.x + w - r, tl.y},
            Point{tl.x + r, tl.y}
        }, corners{
            {std::make_unique<Pie>(Point{tl.x + r, tl.y + r}, r, r, 90, 90)},
            {std::make_unique<Pie>(Point{tl.x + r, tl.y + h - r}, r, r, 180, 90)},
            {std::make_unique<Pie>(Point{tl.x + w - r, tl.y + h - r}, r, r, 270, 90)},
            {std::make_unique<Pie>(Point{tl.x + w - r, tl.y + r}, r, r, 0, 90)}
        }
    {
        if (std::min(w, h) / 2 < r)
            throw std::runtime_error{"invalid size"};
    }

    void draw_specifics(Painter& painter) const override {
        Polygon::draw_specifics(painter);
        for (Pie* p : corners)
            p->draw_specifics(painter);
    }
    void move(int dx, int dy) override {
        Polygon::move(dx, dy);
        for (Pie* p : corners)
            p->move(dx, dy);
    }
private:
    Vector_ref<Pie> corners;
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
    const std::string label = "Box";
    Simple_window win{Point{win_x, win_y}, win_width, win_height, label};

    constexpr int b_width = 600;
    constexpr int b_height = 500;
    constexpr int b_radius = 50;
    Box b{Point{(win_width - b_width) / 2, (win_height - b_height) / 2}, b_width, b_height, b_radius};
    b.set_fill_color(Color::dark_magenta);
    b.set_color(Color::invisible);
    win.attach(b);

    constexpr int b2_width = b_width / 2;
    constexpr int b2_height = b_height / 2;
    constexpr int b2_radius = b_radius / 2;
    Box b2{Point{(win_width - b2_width) / 2, (win_height - b2_height) / 2}, b2_width, b2_height, b2_radius};
    b2.set_fill_color(Color::red);
    b2.set_color(Color::invisible);
    win.attach(b2);

    constexpr int b3_width = b2_width / 2;
    constexpr int b3_height = b2_height / 2;
    constexpr int b3_radius = b2_radius / 2;
    Box b3{Point{(win_width - b3_width) / 2, (win_height - b3_height) / 2}, b3_width, b3_height, b3_radius};
    b3.set_fill_color(Color::white);
    b3.set_color(Color::invisible);
    win.attach(b3);

    win.wait_for_button();
}
