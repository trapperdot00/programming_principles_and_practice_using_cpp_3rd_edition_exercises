#include "PPP/Simple_window.h"
#include "PPP/Graph.h"

double to_degrees(double rad) {
    return 180 * rad / M_PI;
}

double to_radians(double deg) {
    return deg * M_PI / 180;
}

double get_slope(const Point& p1, const Point& p2) {
    if (p1 == p2)
        throw std::runtime_error{"slope undefined"};
    int delta_x = p2.x - p1.x;
    if (delta_x == 0)   // Prevent division by zero
        return 0;
    int delta_y = p2.y - p1.y;
    return double(delta_y) / delta_x;
}

int get_y_intercept(const Point& p1, const Point& p2) {
    double slope = get_slope(p1, p2);
    if (slope == 0)
        throw std::runtime_error{"no y-intercept"};
    int y_intercept = p1.y - slope * p1.x;
    return y_intercept;
}

int get_y_intercept(double slope, const Point& p) {
    return p.y - slope * p.x;
}

bool vertical(const Point& p1, const Point& p2) {
    if (p1 == p2)
        throw std::runtime_error{"can't determine direction"};
    return p1.x == p2.x;
}

double distance(const Point& p1, const Point& p2) {
    return std::sqrt(std::pow(p2.x-p1.x,2)+std::pow(p2.y-p1.y,2));
}

std::pair<int, int> quadratic_formula(double a, double b, double c) {
    int v1 = (-b+std::sqrt(b*b-4*a*c))/(2*a);
    int v2 = (-b-std::sqrt(b*b-4*a*c))/(2*a);
    return std::make_pair(v1, v2);
}

int get_y(double slope, int y_intercept, int x) {
    return slope*x+y_intercept;
}

std::pair<Point, Point> line_circle_intersect
(double slope, int y_intercept, const Point& center, int radius) {
    double a = 1+std::pow(slope,2);
    double b = 2*slope*y_intercept-2*center.x-2*slope*center.y;
    double c = std::pow(center.x,2)+std::pow(y_intercept,2)
        +std::pow(center.y,2)-std::pow(radius,2)-2*y_intercept*center.y;
    const auto [x1, x2] = quadratic_formula(a, b, c);
    const auto [y1, y2] = std::make_pair(
        get_y(slope, y_intercept, x1), get_y(slope, y_intercept, x2)
    );
    Point p1{x1, y1};
    Point p2{x2, y2};
    return std::make_pair(p1, p2);
}

Point closer(const Point& p, const std::pair<Point, Point>& points) {
    double p1_distance = distance(p, points.first);
    double p2_distance = distance(p, points.second);
    return p1_distance <= p2_distance ? points.first : points.second;
}

std::pair<Point, Point> arrow_points
(const Point& p1, const Point& p2, int radius, double angle_deg) {
    double angle_rad = to_radians(angle_deg/2);
    if (vertical(p1, p2)) {
        int delta_x = std::sin(angle_rad) * radius;
        int delta_y = (p1.y < p2.y ? 1 : -1) * std::cos(angle_rad) * radius;
        Point intercept1{p2.x + delta_x, p2.y - delta_y};
        Point intercept2{p2.x - delta_x, p2.y - delta_y};
        return std::make_pair(intercept1, intercept2);
    }
    double slope = get_slope(p1, p2);
    double l1_slope = std::tan(std::atan(slope) + angle_rad);
    double l2_slope = std::tan(std::atan(slope) - angle_rad);
    int l1_y_intercept = get_y_intercept(l1_slope, p2);
    int l2_y_intercept = get_y_intercept(l2_slope, p2);

    Point intercept1 = closer(p1, line_circle_intersect(l1_slope, l1_y_intercept, p2, radius));
    Point intercept2 = closer(p1, line_circle_intersect(l2_slope, l2_y_intercept, p2, radius));
    return std::make_pair(intercept1, intercept2);
}

struct Arrow : public Line {
    Arrow(const Point& p1, const Point& p2, double radius, double angle)
    : Line(p1, p2) {
        const auto [ap1, ap2] = arrow_points(p1, p2, radius, angle);
        arrowhead.add(Point{p2.x, p2.y});
        arrowhead.add(ap1);
        arrowhead.add(ap2);
        set_fill_color(Color::black);
    }
    void set_color(Color c) {
        Line::set_color(c);
        arrowhead.set_color(c);
    }
    void set_fill_color(Color c) {
        arrowhead.set_fill_color(c);
    }
    void draw_specifics(Painter& painter) const override {
        Line::draw_specifics(painter);
        arrowhead.draw(painter);
    }

private:
    Polygon arrowhead;
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
    constexpr int win_height = 700;
    const std::string label = "Arrow";
    Simple_window win{Point{win_x, win_y}, win_width, win_height, label};

    Arrow a{Point{50, 100}, Point{50, 600}, 50, 90};
    Arrow b{Point{100, 600}, Point{100, 100}, 70, 25};
    Arrow c{Point{150, 600}, Point{750, 100}, 100, 10};
    Arrow d{Point{750, 600}, Point{150, 100}, 100, 10};
    Arrow e{Point{450, 100}, Point{450, 600}, 200, 50};

    c.set_color(Color::red);
    c.set_fill_color(Color::yellow);
    d.set_color(Color::blue);
    d.set_fill_color(Color::magenta);

    win.attach(a);
    win.attach(b);
    win.attach(c);
    win.attach(d);
    win.attach(e);
    win.wait_for_button();
}
