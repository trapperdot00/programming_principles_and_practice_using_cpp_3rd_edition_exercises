#include "PPP/Simple_window.h"
#include "PPP/Graph.h"

class Rounded : public Lines {
public:
    Rounded(Point p, int w, int h, int r)
        : Lines{
            Point{p.x, p.y + r}, Point{p.x, p.y + h - r},
            Point{p.x + r, p.y + h}, Point{p.x + w - r, p.y + h},
            Point{p.x + w, p.y + h - r}, Point{p.x + w, p.y + r},
            Point{p.x + w - r, p.y}, Point{p.x + r, p.y}
        }
    {
        if (std::min(w, h) / 2 < r)
            throw std::runtime_error{"invalid radius"};
        create_corners(r);
    }
    Rounded(Point p1, Point p2, int r)
        : Rounded(p1, p2.x - p1.x, p2.y - p1.y, r)
    {}

    void draw_specifics(Painter& painter) const override {
        Lines::draw_specifics(painter);
        for (Arc* p : c)
            p->draw_specifics(painter);
    }

private:
    std::unique_ptr<Arc> create_corner
    (Point p, int r, double st, double rot) const {
        return std::make_unique<Arc>(p, r, r, st, rot);
    }

    void create_corners(int r) {
        for (int i = 0; i < 4; ++i) {
            int curr = (i * 2) % number_of_points();
            int prev = curr > 0 ? curr - 1 : number_of_points() - 1;
            if (i && i % 2)
                swap(prev, curr);
            c.push_back(create_corner(Point{point(prev).x, point(curr).y}, r, (i + 1) * 90, 90));
        }
    }
    Vector_ref<Arc> c;
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
    const std::string label = "Rounded";
    Simple_window win{Point{win_x, win_y}, win_width, win_height, label};

    constexpr Point center{win_width / 2, win_height / 2};
    constexpr int r_width = 200;
    constexpr int r_height = 200;
    Rounded r1{Point{center.x - r_width / 2, center.y - r_height / 2}, r_width, r_height, 20};
    win.attach(r1);

    Rounded r2{Point{0,0}, Point{win_width, win_height}, 50};
    win.attach(r2);

    win.wait_for_button();
}
