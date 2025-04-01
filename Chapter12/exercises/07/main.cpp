#include "PPP/Simple_window.h"
#include "PPP/Graph.h"

class Line_data {
public:
    Line_data(Point a, Point b)
        : m{double(b.y - a.y) / (b.x - a.x)},
        b{int(a.y - m * a.x)}
    {}
    double slope() const { return m; }
    int y_intercept() const { return b; }
private:
    double m;
    int b;
};

// Calculates an intersection between a line and a horizontal line
int intersection(Point p1, Point p2, int y) {
    if (p1.y == p2.y)
        throw std::runtime_error{"parallel lines"};
    if (!((p1.y <= y && y <= p2.y) || (p2.y <= y && y <= p1.y)))
        throw std::runtime_error{"y out of range in intersection()"};
    if (p1.x == p2.x)
        return p1.x;
    Line_data ld{p1, p2};
    int x = (y - ld.y_intercept()) / ld.slope();
    return x;
}

class Striped_closed_polyline : public Closed_polyline {
public:
    void add(Point p) {
        Closed_polyline::add(p);
        update_y_min(p);
        update_y_max(p);
        update_stripes();
    }
    void draw_specifics(Painter& painter) const override {
        Closed_polyline::draw_specifics(painter);
        stripes->draw_specifics(painter);
    }
    int spacing() const { return sp; }
    void set_spacing(int i) { sp = i; update_stripes(); }
private:
    // Calculate intersections between a horizontal line and all sides
    // Returns a list of x-coordinates
    std::vector<int> intersections(int y) const {
        if (y < y_min || y > y_max)
            throw std::runtime_error{"y out of range in intersections()"};
        std::vector<int> points;
        int point_no = number_of_points();
        for (int i = 0; i < point_no; ++i) {
            Point p1 = point(i ? i - 1 : point_no - 1);
            Point p2 = point(i);
            if ((p1.y != p2.y) && ((p1.y <= y && y <= p2.y) || (p2.y <= y && y <= p1.y)))
                points.push_back(intersection(p1, p2, y));
        }
        std::sort(points.begin(),points.end());
        return points;
    }
    void update_y_min(Point p) {
        if (number_of_points() == 1 || p.y < y_min)
            y_min = p.y;
    }
    void update_y_max(Point p) {
        if (number_of_points() == 1 || p.y > y_max)
            y_max = p.y;
    }
    void update_stripes() {
        stripes.reset(new Lines);
        for (int y = y_min + sp; y < y_max; y += sp) {
            std::vector<int> ps = intersections(y);
            for (size_t i = 1; i < ps.size(); i += 2) {
                stripes->add(Point{ps[i - 1], y}, Point{ps[i], y});
            }
        }
    }
    int y_min = 0;
    int y_max = 0;
    int sp = 4;
    std::unique_ptr<Lines> stripes;
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
    const std::string label = "Striped_closed_polyline";
    Simple_window win{Point{win_x, win_y}, win_width, win_height, label};

    // Coordinates and step
    constexpr int center_x = win_width / 2;
    constexpr int center_y = win_height / 2;
    constexpr int x_step = win_width / 5;
    constexpr int y_step = win_height / 5;

    // Pattern
    Striped_closed_polyline scp1;
    scp1.add(Point{center_x, center_y});
    scp1.add(Point{center_x + 2 * x_step, center_y + 2 * y_step});
    scp1.add(Point{center_x - 2 * x_step, center_y + 2 * y_step});
    scp1.add(Point{center_x, center_y});
    scp1.add(Point{center_x - x_step, center_y - y_step});
    scp1.add(Point{center_x - 2 * x_step, center_y});
    scp1.add(Point{center_x - 2 * x_step, center_y - 2 * y_step});
    scp1.add(Point{center_x + 2 * x_step, center_y - 2 * y_step});
    scp1.add(Point{center_x + 2 * x_step, center_y});
    scp1.add(Point{center_x + x_step, center_y - y_step});
    win.attach(scp1);

    // Stylize
    scp1.set_fill_color(Color::cyan);
    scp1.set_style(Line_style{Line_style::solid, 2});
    scp1.set_spacing(12);

    win.wait_for_button();
}
