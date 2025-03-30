#include "PPP/Simple_window.h"
#include "PPP/Graph.h"

struct Striped_rectangle : public Rectangle {
    Striped_rectangle(Point x, Point y)
        : Rectangle{x, y}
    {
        for (int y_pos = x.y + spacing; y_pos < y.y; y_pos += spacing)
            stripes.add(Point{x.x, y_pos}, Point{y.x, y_pos});
    }
    Striped_rectangle(Point p, int w, int h)
        : Rectangle{p, w, h}
    {
        for (int y_pos = p.y + spacing; y_pos < p.y + h; y_pos += spacing)
            stripes.add(Point{p.x, y_pos}, Point{p.x + w, y_pos});
    }

    void move(int dx, int dy) override {
        Rectangle::move(dx, dy);
        stripes.move(dx, dy);
    }
    void draw_specifics(Painter& painter) const override {
        Rectangle::draw_specifics(painter);
        stripes.draw_specifics(painter);
    }
private:
    Lines stripes;
    // Space between stripes
    static constexpr int spacing = 4;
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
    const std::string label = "Striped_rectangle";
    Simple_window win{Point{win_x, win_y}, win_width, win_height, label};

    Striped_rectangle r1{Point{50, 100}, Point{350, 400}};
    r1.set_color(Color::red);

    Striped_rectangle r2{Point{450, 100}, 300, 300};
    r2.set_color(Color::dark_cyan);

    win.attach(r1);
    win.attach(r2);
    win.wait_for_button();
}
