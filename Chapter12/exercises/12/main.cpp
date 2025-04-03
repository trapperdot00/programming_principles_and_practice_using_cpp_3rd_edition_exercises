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

class Pseudo_window {
public:
    Pseudo_window(Point tl, int w, int h, const std::string& s)
        : b{tl, w, h, c_radius},
        l{Point{tl.x, tl.y + 20}, Point{tl.x + w, tl.y + 20}},
        t{tl, s}
    {
        b.set_color(Color::invisible);
        b.set_fill_color(Color{100, 100, 100});
        t.set_color(Color::white);
    }
    void attach_to(Window& w) {
        w.attach(b);
        w.attach(l);
        w.attach(t);
    }
private:
    Box b;
    Line l;
    Text t;
    static int c_radius;
};

int Pseudo_window::c_radius = 10;

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
    const std::string label = "Pseudo_window";
    Simple_window win{Point{win_x, win_y}, win_width, win_height, label};

    Pseudo_window ps{Point{100, 100}, 600, 400, "Pseudo_window"};

    ps.attach_to(win);
    win.wait_for_button();
}
