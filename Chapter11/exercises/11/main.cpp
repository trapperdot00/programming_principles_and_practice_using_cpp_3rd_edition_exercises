#include "PPP/Simple_window.h"
#include "PPP/Graph.h"

int main(int /*argc*/, char * /*argv*/[])
{
    // Color matrix sizes
    constexpr int width = 32;
    constexpr int height = 8;
    constexpr int tile_width = 24;
    constexpr int tile_height = 24;
    constexpr int left = 10;
    constexpr int top = 100;

    // Make Graph_lib's contents available implicitly without using its scope
    using namespace Graph_lib;
    // Initialize display engine
    Application app;
    // Create window
    constexpr int win_x = 200;
    constexpr int win_y = 100;
    constexpr int win_width = width*tile_width + 2*left;
    constexpr int win_height = height*tile_height + 2*top;
    const std::string label = "Color matrix";
    Simple_window win{Point{win_x, win_y}, win_width, win_height, label};

    Vector_ref<Rectangle> vec;
    int color_index = 0;
    for (int column = 0; column < width; ++column) {
        for (int row = 0; row < height; ++row) {
            const Point p{Point{column * tile_width + left, row * tile_height + top}};
            vec.push_back(std::make_unique<Rectangle>(p, tile_width, tile_height));
            // Use shorthand
            Rectangle& r = vec[vec.size() - 1];
            r.set_fill_color(color_index++);
            r.set_color(Color::invisible);
            win.attach(r);
        }
    }

    win.wait_for_button();
}
