#include "PPP/Simple_window.h"
#include "PPP/Graph.h"

class Rounded : public Rectangle {
public:
    Rounded(Point p, int w, int h)
        : Rectangle{p, w, h}
    {
        create_corners(w / 4, h / 4);
    }
    Rounded(Point p1, Point p2)
        : Rectangle{p1, p2}
    {
        create_corners(p2.x - p1.x, p2.y - p1.y);
    }
    void draw_specifics(Painter& painter) const override {
        Rectangle::draw_specifics(painter);
        for (Arc* p : c)
            p->draw_specifics(painter);
    }
private:
    std::unique_ptr<Arc> create_corner
    (Point p, int w, int h, double st, double rot) const {
        return std::make_unique<Arc>(p, w, h, st, rot);
    }
    void create_corners(int w, int h) {
        for (int i = 0; i < 4; ++i) {
            double angle = M_PI / 2 * i;
            Point p{100, 100};
            c.push_back(create_corner(p, w, h, angle, 90));
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

    Rounded r{Point{100, 100}, 200, 200};
    win.attach(r);

    win.wait_for_button();
}
