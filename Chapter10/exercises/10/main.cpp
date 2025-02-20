#include "PPP/Simple_window.h"
#include "PPP/Graph.h"

#include <set>
#include <optional>
#include <cmath>

struct Attributes {
    // Window
    inline static constexpr Point window_pos{200, 200};
    inline static constexpr int window_width = 800;
    inline static constexpr int window_height = 500;
    inline static const std::string window_label = "Source file diagram";

    // Spacing
    inline static constexpr int x_text_spacing = 8;
    inline static constexpr int y_text_spacing = 6;
    inline static constexpr int normal_y_title_spacing = 14;
    // For text that has low-reaching characters (q, p, g etc.)
    inline static constexpr int big_y_title_spacing = normal_y_title_spacing + 4;

    static int determine_y_spacing(const std::string& s) {
        static const std::set<char> lows = {'Q', 'J', 'q', 'y', 'p', 'g', 'j'};
        for (char c : s)
            if (lows.find(c) != lows.cend())
                return big_y_title_spacing;
        return normal_y_title_spacing;
    }

    // Title
    inline static constexpr int title_size = 12;
    inline static const Color title_color = Color::dark_blue;
    inline static const Font title_font = Font::helvetica_bold;

    // Text
    inline static constexpr int text_size = 12;
    inline static const Color text_color = Color::dark_blue;
    inline static const Font text_font = Font::helvetica_bold;

    // Comment
    inline static constexpr int comment_size = 14;
    inline static const Color comment_color = Color::black;
    inline static const Font comment_font = Font::times_bold;

    // Box
    inline static const Color box_fill_color = Color::yellow;
    inline static constexpr int normal_box_width = 200;
    inline static constexpr int normal_box_height = 32;
    inline static constexpr int big_box_width = normal_box_width + 40;
    inline static constexpr int big_box_height = normal_box_height + 48;

    // Line
    inline static const Color line_color = Color::black;

    // Arrow
    inline static const Color arrowhead_color = Color::black;
    inline static constexpr int arrowhead_angle = 25;
    inline static constexpr int arrowhead_height = 20;
};

class Handler {
public:
    static void handle_titles(Window& win, std::vector<Text*>& titles) {
        for (Text* p : titles) {
            p->set_font_size(Attributes::title_size);
            p->set_color(Attributes::title_color);
            p->set_font(Attributes::title_font);
            win.attach(*p);
        }
    }
    static void handle_text(Window& win, std::vector<Text*>& text) {
        for (Text* p : text) {
            p->set_font_size(Attributes::text_size);
            p->set_color(Attributes::text_color);
            p->set_font(Attributes::text_font);
            win.attach(*p);
        }
    }
    static void handle_comments(Window& win, std::vector<Text*>& comments) {
        for (Text* p : comments) {
            p->set_font_size(Attributes::comment_size);
            p->set_color(Attributes::comment_color);
            p->set_font(Attributes::comment_font);
            win.attach(*p);
        }
    }
    static void handle_boxes(Window& win, std::vector<Rectangle*>& boxes) {
        for (Rectangle* p : boxes) {
            p->set_fill_color(Attributes::box_fill_color);
            win.attach(*p);
        }
    }
    static void handle_lines(Window& win, std::vector<Line*>& lines) {
        for (Line* p : lines) {
            p->set_color(Attributes::line_color);
            win.attach(*p);
        }
    }
    static void handle_arrowheads(Window& win, std::vector<Polygon*> arrowheads) {
        for (Polygon* p : arrowheads) {
            p->set_fill_color(Attributes::arrowhead_color);
            win.attach(*p);
        }
    }
};

// -------------------

struct GenericVector {
    int delta_x;
    int delta_y;
};
struct DirectionVector;
struct NormalVector : public GenericVector {
    operator DirectionVector() const;
};
struct DirectionVector : public GenericVector {
    operator NormalVector() const {
        return NormalVector{delta_y, -delta_x};
    }
};
NormalVector::operator DirectionVector() const {
    return DirectionVector{-delta_y, delta_x};
}

struct Circle_data {
    Point center;
    double radius;
};

std::ostream& operator<<(std::ostream& os, const Circle_data& p) {
    return os << "(x-" << -p.center.x << ")^2 + (y-" << -p.center.y << ")^2 = " << std::pow(p.radius, 2);
}

std::pair<int, int> quadratic_formula(double a, double b, double c) {
    int x1 = (-b + std::sqrt(std::pow(b, 2) - 4 * a * c)) / (2 * a);
    int x2 = (-b - std::sqrt(std::pow(b, 2) - 4 * a * c)) / (2 * a);
    return std::make_pair(x1, x2);
}

std::ostream& operator<<(std::ostream& os, const Point& p) {
    return os << '(' << p.x << ';' << p.y << ')';
}

double get_slope(const Point& p1, const Point& p2) {
    if (p1 == p2)
        throw std::runtime_error{"points don't differ"};
    int delta_x = p2.x - p1.x;
    int delta_y = p2.y - p1.y;
    double slope = double(delta_y) / delta_x;
    return slope;
}

double get_slope(const GenericVector& v) {
    if (v.delta_y == 0) {
        if (v.delta_x == 0)
            throw std::runtime_error{"null vector"};
        return 0;
    }
    double slope = v.delta_y / v.delta_x;
    return slope;
}

bool vertical(const Point& p1, const Point& p2) {
    int delta_x = p2.x - p1.x;
    return delta_x == 0;
}
bool upwards(const Point& p1, const Point& p2) {
    int delta_y = p2.y - p1.y;
    return delta_y < 0;
}

int get_y_intercept(double slope, const Point& p) {
    double y_intercept = -slope * p.x + p.y;
    return y_intercept;
}

double distance(const Point& p1, const Point& p2) {
    double d = std::sqrt(std::pow(p2.x-p1.x,2)+std::pow(p2.y-p1.y,2));
    return d;
}

class Line_data {
public:
    Line_data(double s, int y) : s_(s), y_(y) {}
    Line_data(const Point& p1, const Point& p2)
        : s_{get_slope(p1, p2)}, y_(get_y_intercept(s_, p1))
    {}
    Line_data(double s, const Point& p)
        : s_{s}, y_{get_y_intercept(s_, p)}
    {}
    Line_data(const DirectionVector& v, const Point& p)
        : s_{get_slope(v)}, y_{get_y_intercept(s_, p)}
    {}
    Line_data(const NormalVector& v, const Point& p)
        : Line_data(static_cast<DirectionVector>(v), p)
    {}

    // y = mx + b
    int get_y(int x) const {
        return slope() * x + y_intercept();
    }
    // y = mx + b
    // y - mx = b
    // -mx = b - y
    // x = (b - y) / -m
    int get_x(int y) const {
        double x = (y_intercept() - y) / -slope();
        return x;
    }

    double slope() const { return s_;  }
    int y_intercept() const { return y_; }
private:
    double s_;
    int y_;
};

std::ostream& operator<<(std::ostream& os, const Line_data& l) {
    return os << "y = " << l.slope() << "x + " << l.y_intercept();
}

Point intersection(const Line_data& l1, const Line_data& l2) {
    if (l1.slope() == l2.slope())
        throw 0;
    int x = (l1.y_intercept() - l2.y_intercept())
        / (l2.slope() - l1.slope());
    int y = l1.get_y(x);
    return Point{ x, y };
}

std::pair<Point, Point> intersection(const Line_data& line, const Circle_data& circle) {
    double a = 1 + std::pow(line.slope(), 2);
    double b = 2 * line.slope() * line.y_intercept() - 2 * circle.center.x - 2 * line.slope() * circle.center.y;
    double c = std::pow(line.y_intercept(), 2) + std::pow(circle.center.x, 2) + std::pow(circle.center.y, 2)
        - std::pow(circle.radius, 2) - 2 * line.y_intercept() * circle.center.y;
    auto [x1, x2] = quadratic_formula(a, b, c);
    auto [y1, y2] = std::pair{ line.get_y(x1), line.get_y(x2) };

    return std::pair{ Point{x1, y1}, Point{x2, y2} };
}

Point get_closer(const std::pair<Point, Point>& possible, const Point& p) {
    if (distance(possible.first, p) < distance(possible.second, p))
        return possible.first;
    return possible.second;
}

double to_radians(int degrees) {
    return degrees * (M_PI / 180);
}

std::pair<Point, Point> get_arrowhead_coordinates(const Point& start, const Point& end) {
    Circle_data circle{end, Attributes::arrowhead_height};
    double arrow_angle = to_radians(Attributes::arrowhead_angle / 2);
    if (vertical(start, end)) {
        int delta_x = std::tan(arrow_angle) * Attributes::arrowhead_height;
        Point p1{end.x - delta_x, end.y + Attributes::arrowhead_height};
        Point p2{end.x + delta_x, end.y + Attributes::arrowhead_height};
        return std::make_pair(p1, p2);
    }
    Line_data line{start, end};
    double slope1 = std::tan(std::atan(line.slope()) + std::tan(arrow_angle));
    double slope2 = std::tan(std::atan(line.slope()) - std::tan(arrow_angle));
    Line_data arrow_line1{slope1, end};
    Line_data arrow_line2{slope2, end};
    Point p1 = get_closer(intersection(arrow_line1, circle), start);
    Point p2 = get_closer(intersection(arrow_line2, circle), start);
    return std::make_pair(p1, p2);
}

int main(int /*argc*/, char * /*argv*/[])
{
    // Make Graph_lib's contents available implicitly without using its scope
    using namespace Graph_lib;

    // Initialize display engine
    Application app;

    // Create window
    Simple_window win{
        Attributes::window_pos,
        Attributes::window_width,
        Attributes::window_height,
        Attributes::window_label
    };

    // Point
    std::string point_title_s = "Point.h:";
    Point point_title_pos{0, 0};
    Text point_title{
        point_title_pos,
        point_title_s
    };
    Point point_box_pos{
        point_title_pos.x,
        point_title_pos.y + Attributes::determine_y_spacing(point_title_s)
    };
    Rectangle point_box{
        point_box_pos,
        Attributes::normal_box_width,
        Attributes::normal_box_height
    };
    Point point_text_pos{
        point_box_pos.x + Attributes::x_text_spacing,
        point_box_pos.y + Attributes::y_text_spacing
    };
    Text point_text{point_text_pos, "struct Point{ ... };"};

    // Graph
    std::string graph_title_s = "Graph.h:";
    Point graph_title_pos{
        point_box_pos.x,
        point_box_pos.y + point_box.height() + 60};
    Text graph_title{graph_title_pos, graph_title_s};
    Point graph_box_pos{
        graph_title_pos.x,
        graph_title_pos.y + Attributes::determine_y_spacing(graph_title_s)
    };
    Rectangle graph_box{
        graph_box_pos,
        Attributes::normal_box_width,
        Attributes::big_box_height
    };
    Point graph_text_1_pos{
        graph_box_pos.x + Attributes::x_text_spacing, graph_box_pos.y
    };
    Text graph_text_1{graph_text_1_pos, "// Graphing interface"};
    Point graph_text_2_pos{
        graph_box_pos.x + Attributes::x_text_spacing,
        graph_text_1_pos.y + Attributes::comment_size + Attributes::y_text_spacing
    };
    Text graph_text_2{graph_text_2_pos, "struct Shape { ... };"};
    Point graph_text_3_pos{
        graph_box_pos.x + Attributes::x_text_spacing,
        graph_text_2_pos.y + 3 * Attributes::text_size + Attributes::y_text_spacing
    };
    Text graph_text_3{graph_text_3_pos, "..."};

    // Window
    std::string window_title_s = "Window.h";
    Point window_title_pos{
        point_title_pos.x + point_box.width() + 100,
        point_title_pos.y + 75
    };
    Text window_title{window_title_pos, window_title_s};
    Point window_box_pos{
        window_title_pos.x,
        window_title_pos.y + Attributes::determine_y_spacing(window_title_s)
    };
    Rectangle window_box{
        window_box_pos,
        Attributes::normal_box_width,
        Attributes::big_box_height
    };
    Point window_text_1_pos{
        window_box_pos.x + Attributes::x_text_spacing,
        window_box_pos.y
    };
    Text window_text_1{
        window_text_1_pos,
        "// Window interface"
    };
    Point window_text_2_pos{
        window_box_pos.x + Attributes::x_text_spacing,
        window_text_1_pos.y + Attributes::comment_size + Attributes::y_text_spacing
    };
    Text window_text_2{
        window_text_2_pos,
        "struct Window { ... };"
    };
    Point window_text_3_pos{
        window_box_pos.x + Attributes::x_text_spacing,
        window_text_2_pos.y + 3 * Attributes::text_size + Attributes::y_text_spacing
    };
    Text window_text_3{
        window_text_3_pos,
        "..."
    };

    // GUI
    std::string gui_title_s = "GUI.h:";
    Point gui_title_pos{
        window_title_pos.x + window_box.width() + 80,
        graph_title_pos.y + 4
    };
    Text gui_title{
        gui_title_pos, gui_title_s
    };
    Point gui_box_pos{
        gui_title_pos.x,
        gui_title_pos.y + Attributes::determine_y_spacing(gui_title_s)
    };
    Rectangle gui_box{
        gui_box_pos,
        Attributes::normal_box_width,
        Attributes::big_box_height
    };
    Point gui_text_1_pos{
        gui_box_pos.x + Attributes::x_text_spacing,
        gui_box_pos.y
    };
    Text gui_text_1{
        gui_text_1_pos,
        "// GUI interface"
    };
    Point gui_text_2_pos{
        gui_text_1_pos.x,
        gui_text_1_pos.y + Attributes::comment_size + Attributes::y_text_spacing
    };
    Text gui_text_2{
        gui_text_2_pos,
        "struct Button { ... };"
    };
    Point gui_text_3_pos{
        gui_text_2_pos.x,
        gui_text_2_pos.y + 3 * Attributes::text_size + Attributes::y_text_spacing
    };
    Text gui_text_3{
        gui_text_3_pos,
        "..."
    };

    // Simple_window
    std::string simple_window_title_s = "Simple_window.h:";
    Point simple_window_title_pos{
        window_title_pos.x - (Attributes::big_box_width - Attributes::normal_box_width) / 2,
        window_box_pos.y + window_box.height() + 60
    };
    Text simple_window_title{
        simple_window_title_pos,
        simple_window_title_s
    };
    Point simple_window_box_pos{
        simple_window_title_pos.x,
        simple_window_title_pos.y + Attributes::determine_y_spacing(simple_window_title_s)
    };
    Rectangle simple_window_box{
        simple_window_box_pos,
        Attributes::big_box_width,
        Attributes::big_box_height
    };
    Point simple_window_text_1_pos{
        simple_window_box_pos.x + Attributes::x_text_spacing,
        simple_window_box_pos.y
    };
    Text simple_window_text_1{
        simple_window_text_1_pos,
        "// Simple window interface"
    };
    Point simple_window_text_2_pos{
        simple_window_text_1_pos.x,
        simple_window_text_1_pos.y + Attributes::comment_size + Attributes::y_text_spacing
    };
    Text simple_window_text_2{
        simple_window_text_2_pos,
        "struct Simple_window { ... };"
    };

    // Ch10.cpp
    std::string ch10_title_s = "Ch10.cpp";
    Point ch10_title_pos{
        (simple_window_box_pos.x - graph_box_pos.x + graph_box.width() - Attributes::normal_box_width) / 2,
        simple_window_box_pos.y + simple_window_box.height() + 60
    };
    Text ch10_title{
        ch10_title_pos,
        ch10_title_s
    };
    Point ch10_box_pos{
        ch10_title_pos.x,
        ch10_title_pos.y + Attributes::determine_y_spacing(ch10_title_s)
    };
    Rectangle ch10_box{
        ch10_box_pos,
        Attributes::normal_box_width,
        Attributes::normal_box_height
    };
    Point ch10_text_1_pos{
        ch10_box_pos.x + Attributes::x_text_spacing,
        ch10_box_pos.y
    };
    Text ch10_text_1{
        ch10_text_1_pos,
        "int main() { ... }"
    };

    // Lines
    Point graph_top_center{(graph_box_pos.x + graph_box.width()) / 2, graph_box_pos.y};
    Point point_bottom_center{(point_box_pos.x + 0 + point_box.width()) / 2, point_box_pos.y + point_box.height()};
    Line line1{graph_top_center, point_bottom_center};
    Polygon arrowhead1;
    auto [p1, p2] = get_arrowhead_coordinates(graph_top_center, point_bottom_center);
    arrowhead1.add(point_bottom_center);
    arrowhead1.add(p1);
    arrowhead1.add(p2);

    Point window_left_middle{window_box_pos.x, window_box_pos.y + window_box.height() / 2};
    Line line2{window_left_middle, point_bottom_center};
    Polygon arrowhead2;
    auto [p3, p4] = get_arrowhead_coordinates(window_left_middle, point_bottom_center);
    arrowhead2.add(point_bottom_center);
    arrowhead2.add(p3);
    arrowhead2.add(p4);

    Point gui_left_middle{gui_box_pos.x, gui_box_pos.y + gui_box.height() / 2};
    Point window_right_middle{window_box_pos.x + window_box.width(), window_box_pos.y + window_box.height() / 2};
    Line line3{gui_left_middle, window_right_middle};
    Polygon arrowhead3;
    auto [p5, p6] = get_arrowhead_coordinates(gui_left_middle, window_right_middle);
    arrowhead3.add(window_right_middle);
    arrowhead3.add(p5);
    arrowhead3.add(p6);

    Point simple_window_right_middle{simple_window_box_pos.x + simple_window_box.width(), simple_window_box_pos.y + simple_window_box.height() / 2};
    Point gui_bottom_middle{gui_box_pos.x + gui_box.width() / 2, gui_box_pos.y + gui_box.height()};
    Line line4{simple_window_right_middle, gui_bottom_middle};
    Polygon arrowhead4;
    auto [p7, p8] = get_arrowhead_coordinates(simple_window_right_middle, gui_bottom_middle);
    arrowhead4.add(gui_bottom_middle);
    arrowhead4.add(p7);
    arrowhead4.add(p8);

    Point ch10_top_middle{ch10_box_pos.x + ch10_box.width() / 2, ch10_box_pos.y};
    Point simple_window_bottom_middle{simple_window_box_pos.x + simple_window_box.width() / 2, simple_window_box_pos.y + simple_window_box.height()};
    Line line5{ch10_top_middle, simple_window_bottom_middle};
    Polygon arrowhead5;
    auto [p9, p10] = get_arrowhead_coordinates(ch10_top_middle, simple_window_bottom_middle);
    arrowhead5.add(simple_window_bottom_middle);
    arrowhead5.add(p9);
    arrowhead5.add(p10);

    Point graph_bottom_middle{graph_box_pos.x + graph_box.width() / 2, graph_box_pos.y + graph_box.height()};
    Line line6{ch10_top_middle, graph_bottom_middle};
    Polygon arrowhead6;
    auto [p11, p12] = get_arrowhead_coordinates(ch10_top_middle, graph_bottom_middle);
    arrowhead6.add(graph_bottom_middle);
    arrowhead6.add(p11);
    arrowhead6.add(p12);

    // Pointers to all objects based on their types
    std::vector<Rectangle*> boxes = {
        &point_box, &graph_box, &window_box, &gui_box,
        &simple_window_box, &ch10_box
    };
    std::vector<Text*> titles = {
        &point_title, &graph_title, &window_title, &gui_title,
        &simple_window_title, &ch10_title
    };
    std::vector<Text*> comments = {
        &graph_text_1, &window_text_1, &gui_text_1,
        &simple_window_text_1
    };
    std::vector<Text*> text = {
        &point_text, &graph_text_2, &graph_text_3, &window_text_2,
        &window_text_3, &gui_text_2, &gui_text_3, &simple_window_text_2,
        &ch10_text_1
    };
    std::vector<Line*> lines = {
        &line1, &line2, &line3, &line4, &line5, &line6
    };
    std::vector<Polygon*> arrowheads = {
        &arrowhead1, &arrowhead2, &arrowhead3,
        &arrowhead4, &arrowhead5, &arrowhead6
    };


    // Format and attach objects
    Handler::handle_boxes(win, boxes);
    Handler::handle_titles(win, titles);
    Handler::handle_comments(win, comments);
    Handler::handle_text(win, text);
    Handler::handle_lines(win, lines);
    Handler::handle_arrowheads(win, arrowheads);

    win.wait_for_button();
}
