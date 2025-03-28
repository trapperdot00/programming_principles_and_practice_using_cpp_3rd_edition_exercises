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

void tile_with_right_triangles
(Vector_ref<Right_triangle>& vec, Point topleft, int tile_columns, int tile_rows, int tile_width, int tile_height) {
    for (int row = 0; row < tile_rows; ++row) {
        for (int col = 0; col < tile_columns; ++col) {
            Point p1{topleft.x + col * tile_width, topleft.y + row * tile_height};
            Point p2{p1.x + tile_width, p1.y + tile_height};
            vec.push_back(std::make_unique<Right_triangle>(p1, tile_width, -tile_height));
            vec.push_back(std::make_unique<Right_triangle>(p2, -tile_width, tile_height));
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
    const std::string label = "Right triangle tiling";
    Simple_window win{Point{win_x, win_y}, win_width, win_height, label};

    constexpr int tile_columns = 10;
    constexpr int tile_rows = 10;
    const std::array<Color, 2> colors = {{Color::yellow, Color::dark_cyan}};

    constexpr int tile_width = win_width / tile_columns;
    constexpr int tile_height = win_height / tile_rows;

    Vector_ref<Right_triangle> right_triangles;
    tile_with_right_triangles(right_triangles, Point{0,0}, tile_columns, tile_rows, tile_width, tile_height);
    color_each(right_triangles, colors);
    for (Right_triangle* r : right_triangles) {
        win.attach(*r);
    }
    win.wait_for_button();
    win.close();
}
