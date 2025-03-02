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

struct Box : public Rectangle {
    Box(const Point& p, int ww, int hh, const std::string& t)
        : Rectangle(p, ww, hh), text(p, t) {}
    enum Direction {
        TOP, BOTTOM, RIGHT, LEFT, CENTER, TOP_RIGHT, BOTTOM_RIGHT, BOTTOM_LEFT, TOP_LEFT
    };
    void set_color(Color c) {
        Rectangle::set_color(c);
    }
    void set_fill_color(Color c) {
        Rectangle::set_fill_color(c);
    }
    void draw_specifics(Painter& painter) const override {
        Rectangle::draw_specifics(painter);
        text.draw(painter);
        for (Arrow* p : arrows)
            p->draw_specifics(painter);
    }
    void add_arrow(const Point& p2, Direction d) {
        Point p1;
        switch (d) {
        case TOP:
            p1 = n(*this);
            break;
        case BOTTOM:
            p1 = s(*this);
            break;
        case RIGHT:
            p1 = e(*this);
            break;
        case LEFT:
            p1 = ::w(*this);    // don't call Rectangle::w, call the global one
            break;
        case CENTER:
            p1 = center(*this);
            break;
        case TOP_RIGHT:
            p1 = ne(*this);
            break;
        case BOTTOM_RIGHT:
            p1 = se(*this);
            break;
        case BOTTOM_LEFT:
            p1 = sw(*this);
            break;
        case TOP_LEFT:
            p1 = nw(*this);
            break;
        default:
            throw std::runtime_error{"invalid dir"};
        }
        arrows.push_back(std::make_unique<Arrow>(p1, p2, arrowhead_radius, arrowhead_angle));
    }
    void set_font(Font f) {
        text.set_font(f);
    }
    void set_font_size(int i) {
        text.set_font_size(i);
    }
private:
    Vector_ref<Arrow> arrows;
    double arrowhead_radius = 20;
    double arrowhead_angle = 35;
    Text text;
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
    constexpr int win_width = 1000;
    constexpr int win_height = 600;
    const std::string label = "Class diagram";
    Simple_window win{Point{win_x, win_y}, win_width, win_height, label};

    constexpr int box_width = 150;
    constexpr int small_box_width = 124;
    constexpr int box_height = 40;
    constexpr int x_small_spacing = 22;
    constexpr int x_large_spacing = 200;
    Vector_ref<Box> boxes;
    std::array<std::string, 6> top_labels = {
        "Window", "Line_style", "Color",
        "Simple_window", "Shape", "Point"
    };
    std::array<std::string, 7> bottom_labels = {
        "Line", "Lines", "Polygon", "Axis", "Rectangle", "Text", "Image"
    };

    {   // Create top boxes
        int x = 75;
        int y = 50;
        for (size_t i = 0; i < top_labels.size(); ++i) {
            if (x + box_width > win_width) {
                x = 75;
                y += 200;
            }
            Point p{x, y};
            boxes.push_back(std::make_unique<Box>(p, box_width, box_height, top_labels[i]));
            x += box_width + x_large_spacing;
        }
    }
    // Manually connect Simple_window box with Window box with an arrow
    boxes[3].add_arrow(s(boxes[0]), Box::TOP);
    // Create bottom row of boxes, all of which connects to Shape box with an arrow
    for (size_t i = 0; i < bottom_labels.size(); ++i) {
        int x = i * (small_box_width + x_small_spacing);
        Point curr{x, s(boxes[4]).y+100};
        boxes.push_back(std::make_unique<Box>(curr, small_box_width, box_height, bottom_labels[i]));
        boxes[boxes.size()-1].add_arrow(s(boxes[4]), Box::TOP);
    }

    // Stylize and attach all boxes
    for (Box* box : boxes) {
        box->set_fill_color(Color(171, 217, 234));
        box->set_font(Font::times);
        box->set_font_size(16);
        win.attach(*box);
    }

    win.wait_for_button();
}
