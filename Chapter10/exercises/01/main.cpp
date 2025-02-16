#include "PPP/Simple_window.h"
#include "PPP/Graph.h"

// Return the current shape's number (starts at 0)
// If it reaches max, throw
int shape_counter(int max) {
    static int counter = 0;
    if (counter >= max)
        throw std::runtime_error{"reached max shape count"};
    return counter++;
}

// Holds a rectangle's top-left point's coordinates,
// and the width and height
struct Rect_data {
    int x;
    int y;
    int width;
    int height;
};

// Calculate the rectangle's top-left point, width and height that is in the next field
Rect_data get_rect_data(int max_shapes, int equal_width, int margin_factor, int y, int height) {
    int x = equal_width / margin_factor + shape_counter(max_shapes) * equal_width;
    int width = equal_width - 2 * (equal_width / margin_factor);
    return Rect_data{x, y, width, height};
}

int main(int /*argc*/, char * /*argv*/[])
{
    // Make Graph_lib's contents available implicitly without using its scope
    using namespace Graph_lib;

    // Initialize display engine
    Application app;

    // Window top-left point
    constexpr int win_x = 600;
    constexpr int win_y = 400;

    // Dynamic square sizes: scales itself to the window's proportions,
    // just adjust these values to see it in action
    constexpr int win_width = 650;
    constexpr int win_height = 200;

    // Create window
    const std::string win_title = "Rectangle and Polygon";
    Simple_window win{Point{win_x, win_y}, win_width, win_height, win_title};

    // Field count, dictates the fields' sizes, field size always reserved
    constexpr int max_shape_count = 2;

    // Split the window into equal parts vertically to accompany our shapes
    constexpr int equal_width = win_width / max_shape_count;
    constexpr int margin_factor = 6;
    constexpr int y = win_height / margin_factor;
    constexpr int height = win_height - 2 * (win_height / margin_factor);

    // Function call alias that places the arguments into it for us
    auto data = [max_shape_count, equal_width, margin_factor, y, height]() -> Rect_data {
        return get_rect_data(max_shape_count, equal_width, margin_factor, y, height);
    };

    // Create a blue rectangle in the first field
    Rect_data rect1 = data();
    Rectangle rect{Point{rect1.x, rect1.y}, rect1.width, rect1.height};
    rect.set_color(Color::blue);

    // Create a red rectangle using a Polygon in the second field
    Rect_data rect2 = data();
    Polygon poly;
    poly.add(Point{rect2.x, rect2.y + rect2.height});
    poly.add(Point{rect2.x + rect2.width, rect2.y + rect2.height});
    poly.add(Point{rect2.x + rect2.width, rect2.y});
    poly.add(Point{rect2.x, rect2.y});
    poly.set_color(Color::red);

    // Paint our objects onto the window
    win.attach(rect);
    win.attach(poly);

    // Don't exit immediately
    win.wait_for_button();
}
