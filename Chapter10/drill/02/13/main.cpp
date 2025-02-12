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
    Axis xa{Axis::x, Point{20, 300}, 280, 10, "x axis"};
    Axis ya{Axis::y, Point{20, 300}, 280, 10, "y axis"};

    // Create a sine function to plot
    Function sine{dsin, 0, 100, Point{20,150}, 1000, 50, 50};

    // Create a dashed red triangle
    Polygon poly;
    poly.add(Point{300, 200});
    poly.add(Point{350, 100});
    poly.add(Point{400, 200});
    poly.set_color(Color::red);
    poly.set_style(Line_style{Line_style::dash, 4});

    // Create a rectangle filled with yellow
    Rectangle r{Point{200, 200}, 100, 50};
    r.set_fill_color(Color::yellow);

    // Create a polygon of five points filled with green,
    // with dashed lines
    Closed_polyline poly_rect;
    poly_rect.add(Point{100, 50});
    poly_rect.add(Point{200, 50});
    poly_rect.add(Point{200, 100});
    poly_rect.add(Point{100, 100});
    poly_rect.add(Point{50, 75});
    poly_rect.set_fill_color(Color::green);
    poly_rect.set_style(Line_style{Line_style::dash, 2});

    // Create bold text with times font and size set to 20
    Text t{Point{150, 150}, "Hello, graphical world!"};
    t.set_font(Font::times_bold);
    t.set_font_size(20);

    // Create an image of my cat and move it to an appropriate location
    Image cat{Point{100, 50}, "../../cat.png"};
    cat.move(320, 70);

    // Create a circle with an ellipse inside it,
    // with a x-mark in its center point
    Circle c{Point{100, 200}, 50};
    Ellipse e{Point{100, 200}, 75, 25};
    e.set_color(Color::dark_red);
    Mark m{Point{100, 200}, 'x'};
    m.set_color(Color::red);

    // Create text of screen and window resolution sizes
    ostringstream oss;
    oss << "screen size: " << x_max() << '*' << y_max()
        << "; window size: " << win.x_max() << '*' << win.y_max();
    Text sizes{Point{100, 20}, oss.str()};

    // Create another image of my other cat
    Image cat2{Point{200, 235}, "../../cat2.png"};

    // Set the vertical axis' and its label's color
    ya.set_color(Color::cyan);
    ya.label.set_color(Color::dark_red);

    // Add the objects to the window
    win.attach(xa);
    win.attach(ya);
    win.attach(sine);
    win.attach(poly);
    win.attach(r);
    win.attach(poly_rect);
    win.attach(t);
    win.attach(cat);
    win.attach(c);
    win.attach(e);
    win.attach(m);
    win.attach(sizes);
    win.attach(cat2);

    // Change the window frame label
    win.set_label("Final");

    // To keep window on screen
    win.wait_for_button();
}
