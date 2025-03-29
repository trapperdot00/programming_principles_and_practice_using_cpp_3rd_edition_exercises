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
    constexpr int win_width = 800;
    constexpr int win_height = 600;
    const std::string label = "Box with rounded corners (Arc)";
    Simple_window win{Point{win_x, win_y}, win_width, win_height, label};

    Arc a1{Point{win_width / 4, win_height / 4}, 50, 50, 90, 90};
    win.attach(a1);
    Arc a2{Point{win_width / 4, 3 * win_height / 4}, 50, 50, 180, 90};
    win.attach(a2);
    Line l1{Point{win_width / 4 - 50, win_height / 4}, Point{win_width / 4 - 50, 3 * win_height / 4}};
    win.attach(l1);

    Arc a3{Point{3 * win_width / 4, 3 * win_height / 4}, 50, 50, 270, 90};
    win.attach(a3);
    Line l2{Point{win_width / 4, 3 * win_height / 4 + 50}, Point{3 * win_width / 4, 3 * win_height / 4 + 50}};
    win.attach(l2);

    Arc a4{Point{3 * win_width / 4, win_height / 4}, 50, 50, 0, 90};
    win.attach(a4);
    Line l3{Point{3 * win_width / 4 + 50, 3 * win_height / 4}, Point{3 * win_width / 4 + 50, win_height / 4}};
    win.attach(l3);
    Line l4{Point{3 * win_width / 4, win_height / 4 - 50}, Point{win_width / 4, win_height / 4 - 50}};
    win.attach(l4);

    win.wait_for_button();
}
