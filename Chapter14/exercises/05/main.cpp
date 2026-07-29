#include "PPP/Window.h"
#include "PPP/Graph.h"
#include "PPP/GUI.h"
#include "PPP/Image_private.h"
using namespace Graph_lib;

#include <string>
#include <cassert>
#include <sstream>

struct Pane
{
    [[nodiscard]] Pane hsplit(double new_pane_scale = 0.5)
    {
        assert(new_pane_scale > 0 && new_pane_scale < 1);
        Pane a(Point(xy.x, xy.y + h * (1 - new_pane_scale)), w, h * new_pane_scale);
        h *= 1 - new_pane_scale;
        return a;
    }
    [[nodiscard]] Pane vsplit(double new_pane_scale = 0.5)
    {
        assert(new_pane_scale > 0 && new_pane_scale < 1);
        Pane a(Point(xy.x + w * (1 - new_pane_scale), xy.y), w * new_pane_scale, h);
        w *= 1 - new_pane_scale;
        return a;
    }
    Point xy;
    int w;
    int h;
};

Rectangle create_centered_rect(Pane a, int w, int h)
{
    Point p{a.xy.x + (a.w - w) / 2, a.xy.y + (a.h - h) / 2};
    return Rectangle{p, w, h};
}

class Rectangle_mover_window : public Window
{
public:
    Rectangle_mover_window(Point xy, int w, int h, const std::string& title) :
        Window{xy, w, h, title},
        draw_pane{xy, w, h},
        button_pane{draw_pane.vsplit(0.25)},
        input_pane{button_pane.hsplit()},
        output_pane{input_pane.hsplit()},
        rect{create_centered_rect(draw_pane, draw_pane.w / 4, draw_pane.h / 4)},
        coord{rect.point(0)},
        next{button_pane.xy, button_pane.w, button_pane.h, "Next", [this]{ move_to_coord(); }},
        inbox{input_pane.xy, input_pane.w, input_pane.h, "Enter coordinate:", [this]{ read_coord(); }},
        outbox{output_pane.xy, "Set coordinate:", Out_box::Kind::vertical}
    {
        attach(rect);
        rect.set_fill_color(Color::red);
        attach(next);
        attach(inbox);
        inbox.show();
        inbox.hide_buttons();
        attach(outbox);
        update_outbox();
    }
private:
    void move_to_coord()
    {
        int dx = coord.x - rect.point(0).x;
        int dy = coord.y - rect.point(0).y;
        rect.move(dx, dy);
    }
    static std::optional<Point> parse_coord(const std::string& s)
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
    void read_coord()
    {
        if (inbox.last_result() == In_box::accepted)
        {
            std::optional<Point> p = parse_coord(inbox.last_string_value());
            if (p)
            {
                coord = *p;
                update_outbox();
            }
        }
    }
    static std::string to_string(Point p)
    {
        std::ostringstream os;
        os << '(' << p.x << "; " << p.y << ')';
        return os.str();
    }
    void update_outbox()
    {
        outbox.put(to_string(coord));
    }
private:
    Pane draw_pane;
    Pane button_pane;
    Pane input_pane;
    Pane output_pane;
    Rectangle rect;
    Point coord;
    Button next;
    In_box inbox;
    Out_box outbox;
};

int main(int /*argc*/, char* /*argv*/[])
{
    Application app;
    Rectangle_mover_window win{Point{0, 0}, x_max(), y_max(), "Shape mover"};
    app.gui_main();
}
