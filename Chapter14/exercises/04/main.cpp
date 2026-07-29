#include "PPP/Window.h"
#include "PPP/Graph.h"
#include "PPP/GUI.h"
#include "PPP/Image_private.h"
using namespace Graph_lib;

#include <string>
#include <sstream>
#include <memory>
#include <utility>
#include <vector>
#include <optional>
#include <cmath>

Point point_add(Point p, int dx, int dy)
{
    return Point{p.x + dx, p.y + dy};
}

class Hexagon : public Polygon
{
public:
    Hexagon(Point xy, int side_length)
    {
        add(Point{xy.x + side_length / 2, xy.y});
        add(Point{point(0).x + side_length, point(0).y});
        add(Point{xy.x + 2 * side_length, xy.y + height() / 2});
        add(Point{point(1).x, xy.y + height()});
        add(Point{point(0).x, point(3).y});
        add(Point{xy.x, point(2).y});
    }
    Point topleft() const
    {
        return Point{point(0).x - side_length() / 2, point(0).y};
    }
    int side_length() const
    {
        return point(1).x - point(0).x;
    }
    int height() const
    {
        return std::sqrt(3) * side_length();
    }
    int width() const
    {
        return 2 * side_length();
    }
};

class Square : public Rectangle
{
public:
    Square(Point xy, int side_length) :
        Rectangle{xy, side_length, side_length}
    {}
};

class Equilateral_triangle : public Polygon
{
public:
    Equilateral_triangle(Point xy, int side_length) :
        Polygon{
            Point{xy.x + side_length / 2, xy.y},
            Point(xy.x, xy.y + std::sqrt(3) * side_length / 2),
            Point(xy.x + side_length, xy.y + std::sqrt(3) * side_length / 2)
        }
    {}
};

class Shape_placer_window : Window
{
public:
    Shape_placer_window(Point xy, int w, int h, const std::string& title) :
        Window{xy, w, h, title},
        menu{Point{draw_area_width(), 0}, menu_area_width(), menu_area_height() / 2, Menu::vertical, "Shape"},
        inbox{Point{draw_area_width(), menu_area_height() / 2}, menu_area_width(), menu_area_height() / 4, "coordinate", [this]{ handle_inbox(); }},
        outbox{Point{draw_area_width(), 3 * menu_area_height() / 4}, "placing at:", Out_box::Kind::vertical}
    {
        menu.attach(std::make_unique<Button>(Point{draw_area_width(), 0}, menu_area_width(), 20, "Circle", [this]{ place_circle(); }));
        menu.attach(std::make_unique<Button>(Point{draw_area_width(), 0}, menu_area_width(), 20, "Square", [this]{ place_square(); }));
        menu.attach(std::make_unique<Button>(Point{draw_area_width(), 0}, menu_area_width(), 20, "Equilateral Triangle", [this]{ place_equilateral_triangle(); }));
        menu.attach(std::make_unique<Button>(Point{draw_area_width(), 0}, menu_area_width(), 20, "Hexagon", [this] { place_hexagon(); }));
        attach(menu);
        attach(inbox);
        inbox.show();
        inbox.hide_buttons();
        attach(outbox);
        update_outbox();
    }
private:
    int draw_area_width() const
    {
        return x_max() * 0.75;
    }
    int draw_area_height() const
    {
        return y_max();
    }
    int menu_area_width() const
    {
        return x_max() - draw_area_width();
    }
    int menu_area_height() const
    {
        return y_max();
    }

    std::optional<Point> parse_point(const std::string& s)
    {
        std::istringstream is{s};
        Point p;
        char delim;
        if ((is >> p.x >> delim >> p.y) && (delim == ',' || delim == ';'))
        {
            return p;
        }
        return std::nullopt;
    }

    void handle_inbox()
    {
        if (inbox.last_result() == In_box::State::accepted)
        {
            auto p = parse_point(inbox.last_string_value());
            if (p)
            {
                place_pos = *p;
                update_outbox();
            }
        }
    }

    void update_outbox()
    {
        std::ostringstream os;
        os << '(' << place_pos.x << ';' << place_pos.y << ')';
        outbox.put(os.str());
    }

    void place_impl(std::unique_ptr<Shape> s)
    {
        if (s)
        {
            attach(*s);
            shapes.push_back(std::move(s));
        }
    }

    void place_circle()
    {
        int radius = side_length / 2;
        place_impl(std::make_unique<Circle>(point_add(place_pos, radius, radius), radius));
    }

    void place_square()
    {
        place_impl(std::make_unique<Square>(place_pos, side_length));
    }

    void place_equilateral_triangle()
    {
        place_impl(std::make_unique<Equilateral_triangle>(place_pos, side_length));
    }

    void place_hexagon()
    {
        place_impl(std::make_unique<Hexagon>(place_pos, side_length / 2));
    }
private:
    static constexpr int side_length = 200;
    Menu menu;
    In_box inbox;
    Out_box outbox;
    std::vector<std::unique_ptr<Shape>> shapes;
    Point place_pos = Point{0, 0};
};

int main(int /*argc*/, char* /*argv*/[])
{
    Application app;
    Shape_placer_window win{Point{0, 0}, x_max(), y_max(), "Shape placer"};
    app.gui_main();
}
