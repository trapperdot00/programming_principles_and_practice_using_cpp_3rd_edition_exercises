#include "PPP/Simple_window.h"
#include "PPP/Graph.h"

#include <functional>

Point n(const Rectangle& r) {
    return Point{r.point(0).x+r.width()/2,r.point(0).y};
}
Point s(const Rectangle& r) {
    return Point{r.point(0).x+r.width()/2,r.point(0).y+r.height()};
}
Point e(const Rectangle& r) {
    return Point{r.point(0).x+r.width(),r.point(0).y+r.height()/2};
}
Point w(const Rectangle& r) {
    return Point{r.point(0).x,r.point(0).y+r.height()/2};
}
Point center(const Rectangle& r) {
    return Point{r.point(0).x+r.width()/2,r.point(0).y+r.height()/2};
}
Point ne(const Rectangle& r) {
    return Point{r.point(0).x+r.width(),r.point(0).y};
}
Point se(const Rectangle& r) {
    return Point{r.point(0).x+r.width(),r.point(0).y+r.height()};
}
Point sw(const Rectangle& r) {
    return Point{r.point(0).x,r.point(0).y+r.height()};
}
Point nw(const Rectangle& r) {
    return r.point(0);
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
    const std::string label = "Rectangle connection points";
    Simple_window win{Point{win_x, win_y}, win_width, win_height, label};

    constexpr int rect_width = 600;
    constexpr int rect_height = 400;
    Point rect_tl{(win_width - rect_width)/2, (win_height - rect_height)/2};
    Rectangle rect{rect_tl, rect_width, rect_height};
    rect.set_fill_color(Color(125, 125, 125));
    win.attach(rect);

    std::vector<std::function<Point (const Rectangle&)>> positional = {
        n, s, e, w, center, ne, se, sw, nw
    };

    Vector_ref<Mark> marks;
    for (const std::function<Point (const Rectangle&)>& f : positional)
        marks.push_back(std::make_unique<Mark>(f(rect), 'x'));

    for (Mark* p : marks) {
        p->set_color(Color(247, 6, 3));
        win.attach(*p);
    }

    win.wait_for_button();
}
