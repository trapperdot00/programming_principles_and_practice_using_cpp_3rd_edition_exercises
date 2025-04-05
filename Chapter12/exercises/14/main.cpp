#include "PPP/Simple_window.h"
#include "PPP/Graph.h"

class Binary_tree : public Shape {
public:
    Binary_tree(Point c, int r, int levels) : ra{r} {
        construct(c, ra, levels);
    }
    void move(int dx, int dy) override {
        l.move(dx, dy);
        for (Point& p : n) {
            p.x += dx;
            p.y += dy;
        }
    }
    void draw_specifics(Painter &painter) const override {
        l.draw_specifics(painter);
        draw_nodes(painter);
    }
protected:
    virtual void draw_nodes(Painter& painter) const {
        for (Point p : n) {
            painter.draw_ellipse(p, ra, ra);
        }
    }
    int ra;     // Radius of nodes
    Lines l;               // Connecting lines
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
                    l.add(Point{p.x, p.y}, Point{x, y});
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
    const std::string label = "Binary_tree_triangle";
    Simple_window win{Point{win_x, win_y}, win_width, win_height, label};

    Binary_tree_triangle bt{Point{400, 100}, 26, 4};
    bt.set_fill_color(Color::red);
    win.attach(bt);
    bt.move(0, 50);

    win.wait_for_button();
}
