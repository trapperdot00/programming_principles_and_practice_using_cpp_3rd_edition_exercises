#include "PPP/Simple_window.h"
#include "PPP/Graph.h"

int main(int /*argc*/, char * /*argv*/[])
{
    // Make Graph_lib's contents available implicitly without using its scope
    using namespace Graph_lib;

    // Initialize display engine
    Application app;

    // Window top-left point
    constexpr int win_x = 600;
    constexpr int win_y = 400;

    // Window size
    constexpr int win_width = 800;
    constexpr int win_height = 600;

    const std::string label = "Initials";
    Simple_window win{Point{win_x, win_y}, win_width, win_height, label};

    // Create a text object for each letter to be able to manipulate their colors
    Text in1{Point{win_width / 2 - 12, win_height - 150}, "C"};
    in1.set_color(Color::blue);
    Text in2{Point{win_width / 2, win_height - 150}, "R"};
    in2.set_color(Color::dark_green);
    Text in3{Point{win_width / 2 + 12, win_height - 150}, "B"};
    in3.set_color(Color::red);

    // Add a thick straight line
    Line line{Point{0, win_height - 130}, Point{win_width, win_height - 130}};
    line.set_style(Line_style{Line_style::solid, 4});

    win.attach(in1);
    win.attach(in2);
    win.attach(in3);
    win.attach(line);

    // Don't exit immediately
    win.wait_for_button();
}
