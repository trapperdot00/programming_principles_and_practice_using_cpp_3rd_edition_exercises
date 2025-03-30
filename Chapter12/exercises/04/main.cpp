#include "PPP/Simple_window.h"
#include "PPP/Graph.h"

struct Immobile_Circle : public Circle {
    // Inherit constructors
    using Circle::Circle;

private:
    // Cannot delete virtual function in derived, so just
    // make it inaccessible
    using Circle::move;
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
    const std::string label = "Immobile_Circle";
    Simple_window win{Point{win_x, win_y}, win_width, win_height, label};

    Immobile_Circle c1{Point{win_width / 2, win_height / 2}, 200};

    // error
    // c1.move(10, 10);

    win.attach(c1);
    win.wait_for_button();
}
