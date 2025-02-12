#include "PPP/Simple_window.h"
#include "PPP/Graph.h"

double dsin(double d) { return sin(d); }

int main(int /*argc*/, char * /*argv*/[])
{
    using namespace Graph_lib;

    // Window size
    constexpr int win_width = 600;
    constexpr int win_height = 400;

    Application app;
    Point top_left{600, 400};

    // Our window
    Simple_window win{top_left, win_width, win_height, "My window"};

    // Create a horizontal and a vertical axis
    Axis xa{Axis::x, Point{50, 300}, 500, 20, "x axis"};
    Axis ya{Axis::y, Point{50, 300}, 250, 10, "y axis"};

    // Create a sine function to plot
    Function sine{dsin, 0, 100, Point{50,175}, 1000, 25, 100};
    sine.set_color(Color::red);

    // Create a blue parallelogram filled blue
    Polygon poly;
    poly.add(Point{50, 250});
    poly.add(Point{100, 350});
    poly.add(Point{200, 350});
    poly.add(Point{150, 250});
    poly.set_color(Color::blue);
    poly.set_fill_color(Color::blue);

    // Create a rectangle filled yellow with dotted lines
    Rectangle r{Point{50, 275}, 500, 25};
    r.set_fill_color(Color::yellow);
    r.set_style(Line_style{Line_style::dot, 2});

    // Create blue spiky decoration to the left of the vertical axis
    Closed_polyline poly_rect;
    for (int i = 0; i < 11; ++i) {
        int x = (i % 2 == 0) ? 50 : 0;
        poly_rect.add(Point{x, 50 + 25 * i});
    }
    poly_rect.set_fill_color(Color::blue);

    // Set the vertical axis' and its label's color
    ya.set_color(Color::cyan);
    ya.label.set_color(Color::dark_red);

    // Magenta text inside rectangle with an unreadable font :)
    Text t{Point{50, 280}, "Really weird"};
    t.set_color(Color::magenta);
    t.set_font(Font::zapf_dingbats);
    t.set_font_size(18);

    Image cat{Point{400, 15}, "../../cat.png"};
    cat.scale(50, 50);
    cat.move(-175, 185);

    // Create text
    Text t2{Point{250, 150}, "cats cats cats"};
    t2.set_font_size(28);

    // Create another image of my other cat
    Image cat2{Point{200, 150}, "../../cat2.png"};
    cat2.scale(50, 50);

    // Set the vertical axis' and its label's color
    ya.set_color(Color::cyan);
    ya.label.set_color(Color::dark_red);

    // Add the objects to the window
    win.attach(poly);
    win.attach(xa);
    win.attach(ya);
    win.attach(sine);
    win.attach(r);
    win.attach(poly_rect);
    win.attach(t);
    win.attach(cat);
    win.attach(t2);
    win.attach(cat2);

    // Change the window frame label
    win.set_label("Final");

    // To keep window on screen
    win.wait_for_button();
}
