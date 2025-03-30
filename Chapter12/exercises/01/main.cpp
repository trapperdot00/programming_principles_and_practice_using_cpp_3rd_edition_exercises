#include "PPP/Simple_window.h"
#include "PPP/Graph.h"

class Smiley : public Circle {
public:
    Smiley(Point p, int r)
        : Circle{p, r},
        left_eye{Circle{Point{p.x - 3 * r / 8, p.y - 3 * r / 8}, r / 4}},
        right_eye{Circle{Point{p.x + 3 * r / 8, p.y - 3 * r / 8}, r / 4}},
        smile{p, 3 * r / 4, 3 * r / 4, 180, 180}
    {}
    void draw_specifics(Painter &painter) const override {
        Circle::draw_specifics(painter);
        left_eye.draw_specifics(painter);
        right_eye.draw_specifics(painter);
        smile.draw_specifics(painter);
    }
    void move(int dx, int dy) override {
        Circle::move(dx, dy);
        left_eye.move(dx, dy);
        right_eye.move(dx, dy);
        smile.move(dx, dy);
    }

protected:
    Circle left_eye;
    Circle right_eye;
    Arc smile;
};

class Frowny : public Circle {
public:
    Frowny(Point p, int r)
        : Circle{p, r},
        left_eye{Point{p.x - 3 * r / 8, p.y - 3 * r / 8}, r / 4},
        right_eye{Point{p.x + 3 * r / 8, p.y - 3 * r / 8}, r / 4},
        frown{Point{p.x, p.y + 5 * r / 8}, 5 * r / 8, 5 * r / 8 , 0, 180}
    {}
    void draw_specifics(Painter &painter) const override {
        Circle::draw_specifics(painter);
        left_eye.draw_specifics(painter);
        right_eye.draw_specifics(painter);
        frown.draw_specifics(painter);
    }
    void move(int dx, int dy) override {
        Circle::move(dx, dy);
        left_eye.move(dx, dy);
        right_eye.move(dx, dy);
        frown.move(dx, dy);
    }
private:
    Circle left_eye;
    Circle right_eye;
    Arc frown;
};

class Hatted_smiley : public Smiley {
public:
    Hatted_smiley(Point p, int r)
        : Smiley{p, r},
        hat_bottom{Point{p.x - r, p.y - r}, Point{p.x + r, p.y - r}},
        hat_body{Point{p.x - r / 2, p.y - 3 * r}, r, 2 * r}
    {}
    void draw_specifics(Painter& painter) const override {
        Smiley::draw_specifics(painter);
        hat_bottom.draw_specifics(painter);
        hat_body.draw_specifics(painter);
    }
    void move(int dx, int dy) override {
        Smiley::move(dx, dy);
        hat_bottom.move(dx, dy);
        hat_body.move(dx, dy);
    }
private:
    Line hat_bottom;
    Rectangle hat_body;
};

class Hatted_frowny : public Frowny {
public:
    Hatted_frowny(Point p, int r)
        : Frowny{p, r},
        hat_bottom{Point{p.x - r, p.y - r}, Point{p.x + r, p.y - r}},
        hat_body{Point{p.x - r / 2, p.y - r}, Point{p.x, p.y - 3 * r}, Point{p.x + r / 2, p.y - r}}
    {}
    void draw_specifics(Painter& painter) const override {
        Frowny::draw_specifics(painter);
        hat_bottom.draw_specifics(painter);
        hat_body.draw_specifics(painter);
    }
    void move(int dx, int dy) override {
        Frowny::move(dx, dy);
        hat_bottom.move(dx, dy);
        hat_body.move(dx, dy);
    }
private:
    Line hat_bottom;
    Polygon hat_body;
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
    const std::string label = "Smiley and Frowny and their hatted alternatives";
    Simple_window win{Point{win_x, win_y}, win_width, win_height, label};

    constexpr int radius = win_width / 10;
    constexpr int dx = win_width / 8;
    constexpr int y_pos = 2 * win_height / 3;

    Smiley smiley{Point{dx, y_pos}, radius};
    smiley.set_fill_color(Color::magenta);
    smiley.move(0, -50);
    win.attach(smiley);

    Frowny frowny{Point{3 * dx, y_pos}, radius};
    frowny.set_fill_color(Color::dark_red);
    frowny.move(0, -50);
    win.attach(frowny);

    Hatted_smiley hatted_smiley{Point{5 * dx, y_pos}, radius};
    hatted_smiley.set_fill_color(Color::yellow);
    hatted_smiley.move(0, -50);
    win.attach(hatted_smiley);

    Hatted_frowny hatted_frowny{Point{7 * dx, y_pos}, radius};
    hatted_frowny.set_fill_color(Color::dark_cyan);
    hatted_frowny.move(0, -50);
    win.attach(hatted_frowny);

    win.wait_for_button();
}
