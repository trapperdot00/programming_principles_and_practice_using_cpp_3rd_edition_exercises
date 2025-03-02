#include "PPP/Simple_window.h"
#include "PPP/Graph.h"

Point n(const Circle& c) {
    return Point{c.center().x,c.center().y-c.radius()};
}
Point s(const Circle& c) {
    return Point{c.center().x,c.center().y+c.radius()};
}
Point e(const Circle& c) {
    return Point{c.center().x+c.radius(),c.center().y};
}
Point w(const Circle& c) {
    return Point{c.center().x-c.radius(),c.center().y};
}
Point center(const Circle& c) {
    return c.center();
}
Point ne(const Circle& c) {
    return Point{c.center().x+c.radius(),c.center().y-c.radius()};
}
Point se(const Circle& c) {
    return Point{c.center().x+c.radius(),c.center().y+c.radius()};
}
Point sw(const Circle& c) {
    return Point{c.center().x-c.radius(),c.center().y+c.radius()};
}
Point nw(const Circle& c) {
    return c.point(0);
}

Point n(const Ellipse& e) {
    return Point{e.center().x,e.center().y-e.minor()};
}
Point s(const Ellipse& e) {
    return Point{e.center().x,e.center().y+e.minor()};
}
Point e(const Ellipse& e) {
    return Point{e.center().x+e.major(),e.center().y};
}
Point w(const Ellipse& e) {
    return Point{e.center().x-e.major(),e.center().y};
}
Point center(const Ellipse& e) {
    return e.center();
}
Point ne(const Ellipse& e) {
    return Point{e.center().x+e.major(),e.center().y-e.minor()};
}
Point se(const Ellipse& e) {
    return Point{e.center().x+e.major(),e.center().y+e.minor()};
}
Point sw(const Ellipse& e) {
    return Point{e.center().x-e.major(),e.center().y+e.minor()};
}
Point nw(const Ellipse& e) {
    return Point{e.center().x-e.major(),e.center().y-e.minor()};
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
    const std::string label = "Circle and Ellipse connection points";
    Simple_window win{Point{win_x, win_y}, win_width, win_height, label};

    constexpr int circle_radius = 150;
    Point circle_center{win_width/4, win_height/2};
    Circle circle{circle_center, circle_radius};
    circle.set_fill_color(Color(125, 125, 125));
    win.attach(circle);

    // Raw pointers instead of std::function to avoid static_casts for every function
    // required because of the overloads
    std::vector<Point (*)(const Circle&)> circle_positional = {
        n, s, e, w, center, ne, se, sw, nw,
    };

    Vector_ref<Mark> circle_marks;
    for (Point (*&f)(const Circle&) : circle_positional)
        circle_marks.push_back(std::make_unique<Mark>(f(circle), 'x'));

    for (Mark* p : circle_marks) {
        p->set_color(Color(247, 6, 3));
        win.attach(*p);
    }

    constexpr int ellipse_width = 150;
    constexpr int ellipse_height = 200;
    Point ellipse_center{win_width*3/4,win_height/2};
    Ellipse ellipse{ellipse_center,ellipse_width,ellipse_height};
    ellipse.set_fill_color(Color(175, 104, 60));
    win.attach(ellipse);
    std::vector<Point (*)(const Ellipse&)> ellipse_positional = {
        n, s, e, w, center, ne, se, sw, nw
    };

    Vector_ref<Mark> ellipse_marks;
    for (Point (*&f)(const Ellipse&) : ellipse_positional) {
        ellipse_marks.push_back(std::make_unique<Mark>(f(ellipse), 'x'));
    }
    for (Mark* p : ellipse_marks) {
        p->set_color(Color::blue);
        win.attach(*p);
    }

    win.wait_for_button();
}
