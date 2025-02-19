#include "PPP/Simple_window.h"
#include "PPP/Graph.h"

#include <set>
#include <optional>
#include <cmath>

struct Attributes {
    // Window
    inline static constexpr Point window_pos{600, 400};
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

    // Arrow
    inline static constexpr int arrowhead_angle = 50;
    inline static constexpr int arrowhead_height = 10;
};

class Handler {
public:
    static void handle_titles(Window& win, const std::vector<Text*>& titles) {
        for (Text* p : titles) {
            p->set_font_size(Attributes::title_size);
            p->set_color(Attributes::title_color);
            p->set_font(Attributes::title_font);
            win.attach(*p);
        }
    }
    static void handle_text(Window& win, const std::vector<Text*>& text) {
        for (Text* p : text) {
            p->set_font_size(Attributes::text_size);
            p->set_color(Attributes::text_color);
            p->set_font(Attributes::text_font);
            win.attach(*p);
        }
    }
    static void handle_comments(Window& win, const std::vector<Text*>& comments) {
        for (Text* p : comments) {
            p->set_font_size(Attributes::comment_size);
            p->set_color(Attributes::comment_color);
            p->set_font(Attributes::comment_font);
            win.attach(*p);
        }
    }
    static void handle_boxes(Window& win, const std::vector<Rectangle*>& boxes) {
        for (Rectangle* p : boxes) {
            p->set_fill_color(Attributes::box_fill_color);
            win.attach(*p);
        }
    }
};

struct Line_data {
    double slope;
    int y_intercept;
};

Line_data line_from_points(const Point& p1, const Point& p2) {
    int delta_x = p2.x - p1.x;
    int delta_y = p2.y - p1.y;
    double slope = double(delta_y) / delta_x;
    int y_intercept = p1.x * -slope + p1.y;
    return Line_data{slope, y_intercept};
}

int get_y(const Line_data& line, double x) {
    return std::round(x * line.slope + line.y_intercept);
}

struct Circle_data {
    Point center;
    int radius;
};

std::optional<Point> line_line_intersect(const Line_data& l1, const Line_data& l2) {
    if (l1.slope == l2.slope)
        return std::nullopt;
    int x_pos = (l2.y_intercept - l1.y_intercept) / (l1.slope - l2.slope);
    int y_pos = l1.slope * x_pos + l1.y_intercept;
    return Point{x_pos, y_pos};
}

std::pair<int, int> quadratic_formula(double a, double b, double c) {
    double x1 = (-b+std::sqrt(std::pow(b,2)-4*a*c)) / (2*a);
    double x2 = (-b-std::sqrt(std::pow(b,2)-4*a*c)) / (2*a);
    return std::make_pair(x1, x2);
}

std::pair<Point, Point> circle_line_intersect(const Line_data& line, const Circle_data& circle) {
    double a = 1 + std::pow(line.slope, 2);
    double b = 2*line.slope*line.y_intercept - 2*circle.center.x - 2*line.slope*circle.center.y;
    double c = std::pow(line.y_intercept, 2)+std::pow(circle.center.x, 2)+std::pow(circle.center.y, 2)
               - std::pow(circle.radius, 2) - 2*line.y_intercept*circle.center.y;
    auto [x1, x2] = quadratic_formula(a, b, c);
    auto [y1, y2] = std::pair{get_y(line, x1), get_y(line, x2)};

    return {{x1, y1}, {x2, y2}};
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

    /*// Lines
    Point graph_top_center{(graph_box_pos.x + graph_box.width()) / 2, graph_box_pos.y};
    Point point_bottom_center{(point_box_pos.x + point_box.width()) / 2, point_box_pos.y + point_box.height()};
    Line graph_to_point{graph_top_center, point_bottom_center};
    Line_data graph_to_point_data = line_from_points(graph_top_center, point_bottom_center);
    Polygon graph_to_point_head;
    graph_to_point_head.add(point_bottom_center);
    if (std::isfinite(graph_to_point_data.slope)) {
        Circle_data graph_to_point_helper{point_bottom_center, Attributes::arrowhead_height};
        auto [graph_to_point_arrow_p1, graph_to_point_arrow_p2] = circle_line_intersect(graph_to_point_data, graph_to_point_helper);
        graph_to_point_head.add(graph_to_point_arrow_p1);
        graph_to_point_head.add(graph_to_point_arrow_p2);
    } else {

    }
    graph_to_point_head.set_fill_color(Color::black);
*/
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


    // Format and attach objects
    Handler::handle_boxes(win, boxes);
    Handler::handle_titles(win, titles);
    Handler::handle_comments(win, comments);
    Handler::handle_text(win, text);

    //win.attach(graph_to_point);
   // win.attach(graph_to_point_head);

    win.wait_for_button();
}
