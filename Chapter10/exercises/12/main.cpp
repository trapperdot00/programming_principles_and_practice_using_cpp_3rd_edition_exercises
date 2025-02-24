#include "PPP/Simple_window.h"
#include "PPP/Graph.h"

#include <vector>
#include <memory>
#include <stdexcept>

// a: span of x coordinates (e.g. a := 3 -> [-3;3])
// b: span of y coordinates
// scale: size of superellipse
std::unique_ptr<Open_polyline> superellipse
(double a, double b, double m, double n, int N, int dx, int dy, double scale = 1.0) {
    if (m <= 0 || n <= 0)
        throw std::runtime_error{"m and n can't be <= 0"};
    if (N < 2)
        throw std::runtime_error{"not enough points"};
    std::vector<Point> points_pos;  // Points above relative x-axis
    std::vector<Point> points_neg;  // Points below relative x-axis
    double step = a*2 / (N-1);      // Equal distance step between points
    for (int i = 0; i < N; ++i) {
        double x = -a + i*step;     // Go from -a to a
        double y1 = b*std::pow(1-std::pow(std::abs(x/a),m),1/n);
        double y2 = -b*std::pow(1-std::pow(std::abs(x/a),m),1/n);
        // Construct scaled and moved coordinates
        Point p1{dx+int(x*scale), dy+int(y1*scale)};
        Point p2{dx+int(x*scale), dy+int(y2*scale)};
        points_pos.push_back(p1);
        points_neg.push_back(p2);
    }
    std::unique_ptr<Open_polyline> line = std::make_unique<Open_polyline>();
    // Connect upper points from left to right
    for (size_t i = 0; i < points_pos.size(); ++i)
        line->add(points_pos[i]);
    // Connect lower points from right to left
    for (size_t i = points_neg.size(); i > 0; --i)
        line->add(points_neg[i-1]);
    return line;
}

void attach(Window& win, const std::vector<std::unique_ptr<Open_polyline>>& lines) {
    for (const std::unique_ptr<Open_polyline>& p : lines)
        win.attach(*p);
}

int main(int /*argc*/, char * /*argv*/[])
{
    // Make Graph_lib's contents available implicitly without using its scope
    using namespace Graph_lib;

    // Initialize display engine
    Application app;

    // Window top-left point
    constexpr int win_x = 200;
    constexpr int win_y = 100;

    // Create window
    const std::string label = "Superellipse";
    Simple_window win{Point{win_x, win_y}, x_max()/2, y_max()/2, label};

    std::vector<std::unique_ptr<Open_polyline>> lines;
    double m = 0.1;
    int points = x_max();
    for (size_t i = 0; i < 10; ++i) {
        lines.push_back(superellipse(x_max()/2/3, y_max()/2/3, m, m, points, x_max()/2/2, y_max()/2/2, 1.3));
        m *= 1.5;
    }

    attach(win, lines);

    win.wait_for_button();
}
