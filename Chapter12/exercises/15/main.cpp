#include "PPP/Simple_window.h"
#include "PPP/Graph.h"

double slope(Point p1, Point p2) {
    int d = p2.x - p1.x;
    if (!d)
        throw std::runtime_error{"vertical line"};
    return (p2.y - p1.y) / d;
}

bool vertical(Point p1, Point p2) {
    return p2.x == p1.x;
}

std::pair<double, double> quadratic_formula(double a, double b, double c) {
    double x1 = (-b-std::sqrt(b*b-4*a*c))/(2*a);
    double x2 = (-b+std::sqrt(b*b-4*a*c))/(2*a);
    return std::make_pair(x1, x2);
}

std::pair<Point, Point> circle_line_intersection(Point p, int r, int bb, double s) {
    double a = 1+s*s;
    double b = 2*(-p.x+s*(bb-p.y));
    double c = std::pow(p.x,2)-std::pow(r,2)+std::pow(bb-p.y,2);
    auto [x1, x2] = quadratic_formula(a, b, c);
    auto [y1, y2] = std::make_pair(s*x1+bb, s*x2+bb);
    Point p1{int(x1), int(y1)};
    Point p2{int(x2), int(y2)};
    return std::make_pair(p1, p2);
}

double distance(Point p1, Point p2) {
    return std::sqrt(std::pow(p2.x - p1.x, 2) + std::pow(p2.y - p1.y, 2));
}

class Arrowhead : public Polygon {
public:
    Arrowhead(Point p1, Point p2, int ra, double a)
        : r{ra}
    {
        int dx = p2.x - p1.x;
        int dy = p2.y - p1.y;
        double angle = std::atan2(dy, dx);
        Point ap1 = get_arrowhead_point(p2, angle - a);
        Point ap2 = get_arrowhead_point(p2, angle + a);
        Polygon::add(p2);
        Polygon::add(ap1);
        Polygon::add(ap2);
    }
    void draw_specifics(Painter& painter) const override {
        //c.draw_specifics(painter);
        Polygon::draw_specifics(painter);
    }
private:
    Point get_arrowhead_point(Point p, double a) const {
        int dx = r * std::cos(a);
        int dy = r * std::sin(a);
        return Point{p.x - dx, p.y - dy};
    }
    int r;
};

class Binary_tree : public Shape {
public:
    enum class Arrow_direction {
        none, up, down
    };
    Binary_tree(Point c, int r, int levels, Line_style l = Line_style::solid,
                Color co = Color::black, Arrow_direction d = Arrow_direction::none)
        : ra{r}, ls{l}, col{co}, dir{d}
    {
        construct(c, ra, levels);
    }
    void move(int dx, int dy) override {
        for (Line* p : l) {
            p->move(dx, dy);
        }
        for (Point& p : n) {
            p.x += dx;
            p.y += dy;
        }
        for (Arrowhead* p : a) {
            p->move(dx, dy);
        }
    }
    void draw_specifics(Painter &painter) const override {
        draw_nodes(painter);
        draw_lines(painter);
        draw_arrowheads(painter);
    }
protected:
    virtual void draw_nodes(Painter& painter) const {
        for (Point p : n) {
            painter.draw_ellipse(p, ra, ra);
        }
    }
    virtual void draw_lines(Painter& painter) const {
        for (Line* p : l) {
            p->draw(painter);
        }
    }
    virtual void draw_arrowheads(Painter& painter) const {
        for (Arrowhead* p : a)
            p->draw(painter);
    }
    int ra;     // Radius of nodes
    Line_style ls;  // Connecting line style
    Color col;      // Line color
    Arrow_direction dir;
    Vector_ref<Line> l;    // Connecting lines
    Vector_ref<Arrowhead> a;
    std::vector<Point> n;   // Nodes
private:
    void construct(Point c, int r, int levels) {
        const int y_step = 4 * r;
        const int x_step = y_step;
        int y = c.y;
        for (int i = 0; i < levels; ++i) {
            const int nodes = std::pow(2, i);
            // Make it symmetric
            int x = (i ? x_step / 2 : 0) + c.x - nodes / 2 * x_step;
            for (int j = 0; j < nodes; ++j) {
                if (i) {
                    int parent = nodes / 2 - 1 + j / 2;
                    Point p = n[parent];
                    l.push_back(std::make_unique<Line>(Point{p.x, p.y + r}, Point{x, y - r}));
                    switch (dir) {
                    case Arrow_direction::down:
                        a.push_back(std::make_unique<Arrowhead>(Point{p.x, p.y}, Point{x, y - r}, r, M_PI / 6));
                        break;
                    case Arrow_direction::up:
                        a.push_back(std::make_unique<Arrowhead>(Point{x, y - r}, Point{p.x, p.y + r}, r, M_PI / 6));
                        break;
                    default:
                        break;
                    }
                    a[a.size() - 1].set_color(col);
                    a[a.size() - 1].set_fill_color(col);
                    l[l.size() - 1].set_style(ls);
                    a[a.size() - 1].set_style(ls);
                }
                n.push_back(Point{x, y});
                x += x_step;
            }
            y += y_step;
        }
    }
};

class Triangle : public Polygon {
public:
    Triangle(Point center, int radius) {
        constexpr double angle_step = 2 * M_PI / 3;
        double angle = M_PI / 2;
        for (int i = 0; i < 3; ++i) {
            int x = center.x + radius * std::cos(angle);
            int y = center.y - radius * std::sin(angle);
            Polygon::add(Point{x, y});
            angle += angle_step;
        }
    }
    void draw_specifics(Painter& painter) const override {
        Polygon::draw_specifics(painter);
    }
};

class Binary_tree_triangle : public Binary_tree {
public:
    using Binary_tree::Binary_tree;
protected:
    void draw_nodes(Painter& painter) const override {
        for (Point p : n) {
            painter.draw_polygon(Triangle{p, ra});
        }
    }
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
    const std::string label = "Binary_tree lines";

    Simple_window win{Point{win_x, win_y}, win_width, win_height, label};
    Binary_tree bt(Point{400, 100}, 26, 4, Line_style{Line_style::dot, 2}, Color::dark_cyan, Binary_tree::Arrow_direction::up);
    bt.set_fill_color(Color::cyan);
    bt.move(0, 50);
    win.attach(bt);

    win.wait_for_button();
}
