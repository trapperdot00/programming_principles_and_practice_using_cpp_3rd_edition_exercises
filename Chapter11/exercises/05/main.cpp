#include "PPP/Simple_window.h"
#include "PPP/Graph.h"

int main(int /*argc*/, char * /*argv*/[])
{
    // Make Graph_lib's contents available implicitly without using its scope
    using namespace Graph_lib;

    // Initialize display engine
    Application app;

    // Create window
    constexpr int win_x = 200;
    constexpr int win_y = 100;
    constexpr int win_width = 720;
    constexpr int win_height = 300;
    const std::string label = "RGB color chart";
    Simple_window win{Point{win_x, win_y}, win_width, win_height, label};

    Vector_ref<Rectangle> vec;
    constexpr int columns = 32;
    constexpr int rows = 8;
    // Individual rectangle sizes
    constexpr int width = 20;
    constexpr int height = 20;
    // Full scale size
    constexpr int whole_width = columns * width;
    constexpr int whole_height = rows * height;

    Point top_left{(win_width - whole_width)/2, (win_height - whole_height)/2};
    for (int y = 0; y < rows; ++y) {
        for (int x = 0; x < columns; ++x) {
            vec.push_back(std::make_unique<Rectangle>(Point(top_left.x + x * width, top_left.y + y * height), width, height));
            // Calculate colors using HSV to create a smooth gradient of colors
            double hue = 359.0 * x / (columns-1);
            double saturation = 1;
            double value = double(y) / (rows - 1);
            double c = value * saturation;
            double h = hue / 60;
            double xval = c * (1 - std::abs(fmod(h, 2) - 1));
            int m = value - c;
            // Convert HSV to RGB
            int r = 0;
            int g = 0;
            int b = 0;
            if (0 <= h && h < 1) {
                r = 255 * (c + m);
                g = 255 * (xval + m);
            } else if (1 <= h && h < 2) {
                r = 255 * (xval + m);
                g = 255 * (c + m);
            } else if (2 <= h && h < 3) {
                g = 255 * (c + m);
                b = 255 * (xval + m);
            } else if (3 <= h && h < 4) {
                g = 255 * (xval + m);
                b = 255 * (c + m);
            } else if (4 <= h && h < 5) {
                r = 255 * (xval + m);
                b = 255 * (c + m);
            } else if (5 <= h && h < 6) {
                r = 255 * (c + m);
                b = 255 * (xval + m);
            }
            vec[vec.size()-1].set_fill_color(Color(r,g,b));
        }
    }
    for (Rectangle* p : vec)
        win.attach(*p);
    win.wait_for_button();
    win.close();    // skip long destruction animation
}
