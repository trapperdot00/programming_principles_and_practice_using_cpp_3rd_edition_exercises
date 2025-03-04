#include "PPP/Simple_window.h"
#include "PPP/Graph.h"

double to_degrees(double rad) {
    return rad * 180 / M_PI;
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
    const std::string label = "Mark around circle animation";
    Simple_window win{Point{win_x, win_y}, win_width, win_height, label};

    constexpr double scale = 0.8;
    const Point center{win_width / 2, win_height / 2};
    constexpr int radius = std::min(win_width, win_height) / 2 * scale;
    Circle circle{center, radius};
    win.attach(circle);

    constexpr double full_circle = 2*M_PI;
    // Current angle
    double angle = 0;
    // Increment by step on each iteration
    double step = full_circle/20;
    while (true) {
        // Get relative coordinates from the centerpoint
        int dx = radius * std::cos(angle);
        int dy = radius * std::sin(angle);
        // Get absolute coordinates
        int x = center.x + dx;
        int y = center.y - dy;
        Mark m{Point{x, y}, 'x'};
        // Display current angle in degrees
        Text angle_text{center, std::to_string(int(to_degrees(angle))) + "°"};
        win.attach(m);
        win.attach(angle_text);
        win.wait_for_button();
        // Don't let angle exceed the angle of a full_circle
        angle = std::fmod(angle + step, full_circle);
    }
}
