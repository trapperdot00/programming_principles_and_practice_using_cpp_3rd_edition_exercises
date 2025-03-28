#include "PPP/Simple_window.h"
#include "PPP/Graph.h"

struct Right_triangle : public Polygon {
    // Construct a right angle triangle based on
    // its centerpoint (the vertex with the right angle),
    // and its base and its height
    // The base and height values are essentially offsets
    // from the center, accepts negative values to allow "rotation"
    Right_triangle(Point center, int x, int y)
        : Polygon {
            center,
            Point{center.x + x, center.y},
            Point{center.x, center.y - y}
        }
    {}
};

void octagonal_shape(Vector_ref<Right_triangle>& vec, Point topleft, int width, int height) {
    if (width < 3 || height < 3)
        throw std::runtime_error{"invalid size for octagonal shape"};
    width /= 3;
    height /= 3;
    for (int col = 0; col < 3; ++col) {
        for (int row = 0; row < 3; ++row) {
            if (col == 0 && row == 0)
                vec.push_back(std::make_unique<Right_triangle>(Point{topleft.x + width, topleft.y + height}, -width, height));
            else if (col == 2 && row == 0)
                vec.push_back(std::make_unique<Right_triangle>(Point{topleft.x + col * width, topleft.y + height}, width, height));
            else if (col == 0 && row == 2)
                vec.push_back(std::make_unique<Right_triangle>(Point{topleft.x + width, topleft.y + row * height}, -width, -height));
            else if (col == 2 && row == 2)
                vec.push_back(std::make_unique<Right_triangle>(Point{topleft.x + col * width, topleft.y + row * height}, width, -height));
            else if ((col == 1 && row == 0) || (col == 0 && row == 1))
                vec.push_back(std::make_unique<Right_triangle>(Point{topleft.x + col * width, topleft.y + row * height}, width, -height));
            else if ((col == 2 && row == 1) || (col == 1 && row == 2))
                vec.push_back(std::make_unique<Right_triangle>(Point{topleft.x + (col + 1) * width, topleft.y + (row + 1 ) * height}, -width, height));
        }
    }
}

template <size_t N>
void color_each(Vector_ref<Right_triangle>& polygons, const std::array<Color, N>& colors) {
    if (colors.size() == 0)
        throw std::runtime_error{"no colors"};

    size_t color_i = 0;
    for (Polygon* p : polygons) {
        p->set_fill_color(colors[color_i++ % colors.size()]);
    }
}

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
    const std::string label = "Octagonal shape from right triangles";
    Simple_window win{Point{win_x, win_y}, win_width, win_height, label};

    Vector_ref<Right_triangle> right_triangles;
    octagonal_shape(right_triangles, Point{win_width/4,win_height/4}, win_width/2, win_height/2);

    const std::array<Color, 8> colors = {{
        Color::red, Color::blue, Color::yellow, Color::magenta,
        Color::dark_blue, Color::dark_cyan, Color::green, Color::dark_yellow
    }};
    color_each(right_triangles, colors);
    for (Right_triangle* r : right_triangles) {
        win.attach(*r);
    }
    win.wait_for_button();
}
