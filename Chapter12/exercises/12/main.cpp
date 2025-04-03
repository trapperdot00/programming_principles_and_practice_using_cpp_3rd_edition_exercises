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
        l{Point{tl.x, tl.y + top_bar_height}, Point{tl.x + w, tl.y + top_bar_height}},
        t{tl, s},
        mi{Point{tl.x + w - 3 * icon_spacing, tl.y + top_bar_height / 2}, top_bar_height / 3},
        mi_i{
            Point{tl.x + w - 3 * icon_spacing - top_bar_height / 3, tl.y + top_bar_height / 2},
            Point{tl.x + w - 3 * icon_spacing + top_bar_height / 3, tl.y + top_bar_height / 2}
        },
        ma{Point{tl.x + w - 2 * icon_spacing, tl.y + top_bar_height / 2}, top_bar_height / 3},
        ma_i{Point{tl.x + w - 2 * icon_spacing - top_bar_height / 6,
            tl.y + top_bar_height / 2 - top_bar_height / 6}, top_bar_height / 3, top_bar_height / 3
        },
        cl{Point{tl.x + w - icon_spacing, tl.y + top_bar_height / 2}, top_bar_height / 3},
        cl_i{
            Point{tl.x + w - icon_spacing - top_bar_height / 6, tl.y + top_bar_height / 2 - top_bar_height / 6},
            Point{tl.x + w - icon_spacing + top_bar_height / 6, tl.y + top_bar_height / 2 + top_bar_height / 6},
            Point{tl.x + w - icon_spacing - top_bar_height / 6, tl.y + top_bar_height / 2 + top_bar_height / 6},
            Point{tl.x + w - icon_spacing + top_bar_height / 6, tl.y + top_bar_height / 2 - top_bar_height / 6}
        }
    {
        b.set_color(Color::invisible);
        b.set_fill_color(Color{100, 100, 100});
        t.set_color(Color::white);
        mi.set_fill_color(Color::green);
        ma.set_fill_color(Color{255, 200, 0});
        cl.set_fill_color(Color::red);
    }
    void attach_to(Window& w) {
        w.attach(b);
        w.attach(l);
        w.attach(t);
        w.attach(mi);
        w.attach(mi_i);
        w.attach(ma);
        w.attach(ma_i);
        w.attach(cl);
        w.attach(cl_i);
    }
    void move(int dx, int dy) {
        b.move(dx, dy);
        l.move(dx, dy);
        t.move(dx, dy);
        mi.move(dx, dy);
        mi_i.move(dx, dy);
        ma.move(dx, dy);
        ma_i.move(dx, dy);
        cl.move(dx, dy);
        cl_i.move(dx, dy);
    }
    static const int c_radius;        // Corner radius
    static const int top_bar_height;
    static const int icon_spacing;
private:
    Box b;      // Background
    Line l;     // Top bar separator
    Text t;     // Label
    // Control icons
    Circle mi;  // Minimize
    Line mi_i;  // Minimize icon
    Circle ma;  // Maximize
    Rectangle ma_i; // Maximize icon
    Circle cl;  // Close
    Lines cl_i; // Close icon

};

const int Pseudo_window::c_radius = 8;
const int Pseudo_window::top_bar_height = 20;
const int Pseudo_window::icon_spacing = 20;

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

    Pseudo_window ps{Point{100, 100}, 600, 400, "Felis catus"};
    ps.attach_to(win);

    Image i{Point{100 + 600 / 2 - 240 / 2, 100 + 400 / 2 - 287 / 2 + Pseudo_window::top_bar_height / 2}, "../../cat.png"};
    win.attach(i);

    win.wait_for_button();
}
