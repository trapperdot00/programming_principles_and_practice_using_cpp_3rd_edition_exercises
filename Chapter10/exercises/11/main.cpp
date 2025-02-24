#include "PPP/Simple_window.h"
#include "PPP/Graph.h"

#include <cmath>
#include <vector>
#include <memory>

double to_degrees(double rad) {
    return rad * 180 / M_PI;
}
double to_radians(double deg) {
    return deg * M_PI / 180;
}

std::vector<Point> points(int vertices, Point center, int radius) {
    std::vector<Point> point_vec;
    double angle_step = (2 * M_PI) / vertices;
    double angle = (vertices % 2 ? M_PI / 2 : M_PI / 2 + M_PI / vertices);
    for (int i = 0; i < vertices; ++i) {
        int x = std::cos(angle) * radius + center.x;
        int y = -std::sin(angle) * radius + center.y;
        point_vec.push_back(Point{x,y});
        angle += angle_step;
    }
    return point_vec;
}

std::unique_ptr<Polygon> generate_poly(const std::vector<Point>& pvec) {
    std::unique_ptr<Polygon> polygon = std::make_unique<Polygon>();
    for (const Point& p : pvec)
        polygon->add(p);
    return polygon;
}

std::unique_ptr<Polygon> generate_poly(int n, Point center, int radius) {
    std::unique_ptr<Polygon> polygon = std::make_unique<Polygon>();
    std::vector<Point> pvec{points(n, center, radius)};
    for (const Point& p : pvec)
        polygon->add(p);
    return polygon;
}

double distance(const Point& p1, const Point& p2) {
    double delta_x = p2.x - p1.x;
    double delta_y = p2.y - p1.y;
    double d = std::sqrt(std::pow(delta_x, 2) + std::pow(delta_y, 2));
    return d;
}

struct Circle_data {
    Point center;
    int radius;
};

int inradius(const Point& center, const Point& vertex, int sides) {
    double radius = distance(center, vertex);
    int inradius = radius * std::cos(to_radians(180 / sides));
    return inradius;
}

void attach(Window& win, const std::vector<std::unique_ptr<Shape>>& shapes) {
    for (const std::unique_ptr<Shape>& p : shapes)
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

    double scale = 0.9;
    int radius = (x_max() < y_max() ? x_max() / 2 : y_max() / 2) * scale;
    Point center{x_max() / 2, y_max() / 2};

    // Create window
    const std::string label = "Series of enclosed polygons";
    Simple_window win{Point{win_x, win_y}, x_max(), y_max(), label};

    std::array<Color, 3> colors = {Color::red, Color::blue, Color::green};
    std::vector<std::unique_ptr<Shape>> shapes;
    for (int vertices = 7; vertices != 2; --vertices) {
        // Add helper circle
        std::unique_ptr<Circle> helper_circle = std::make_unique<Circle>(center, radius);
        shapes.push_back(std::move(helper_circle));

        // Add polygon
        std::vector<Point> pvec = points(vertices, center, radius);
        std::unique_ptr<Shape> shape = generate_poly(vertices, center, radius);
        shape->set_fill_color(colors[vertices % 3]);
        shapes.push_back(std::move(shape));
        radius = inradius(center, pvec.front(), vertices);
    }
    // Draw all
    attach(win, shapes);

    win.wait_for_button();
}
