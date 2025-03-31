#include "PPP/Simple_window.h"
#include "PPP/Graph.h"

std::pair<int, int> hline_circle_intersection
(int y, Point center, int radius) {
    // Produce two values!
    if (y <= center.y - radius || y >= center.y + radius)
        throw std::runtime_error{"y out of range"};
    int x1 = center.x + std::sqrt(std::pow(radius, 2) - std::pow(y - center.y, 2));
    int x2 = center.x - std::sqrt(std::pow(radius, 2) - std::pow(y - center.y, 2));
    return std::make_pair(x1, x2);
}

struct Striped_circle : public Circle {
    Striped_circle(Point center, int radius)
        : Circle{center, radius}
    {
        // Draw horizontal lines from top to bottom inside circle
        for (int y_pos = center.y - radius + spacing;
             y_pos < center.y + radius;
             y_pos += spacing) {
            auto [x1, x2] = hline_circle_intersection(y_pos, center, radius);
            stripes.add(Point{x1, y_pos}, Point{x2, y_pos});
        }
    }

    void move(int dx, int dy) override {
        Circle::move(dx, dy);
        stripes.move(dx, dy);
    }
    void draw_specifics(Painter &painter) const override {
        Circle::draw_specifics(painter);
        stripes.draw_specifics(painter);
    }
private:
    Lines stripes;
    static constexpr int spacing = 4;
};

template <std::size_t N>
void generate_sine(Vector_ref<Striped_circle>& shapes,
                   const std::array<Color, N>& colors,
                   int win_width,
                   int win_height,
                   int radius,
                   int spacing,
                   double frequency,
                   double amplitude) {
    static_assert(N > 0, "empty color");
    for (int x = 0, i = 0; x <= win_width; x += spacing, ++i) {
        double rad = 2.0 * M_PI * frequency * x / win_width;
        int y = std::sin(rad) * amplitude * win_height / 2 + win_height / 2;
        shapes.push_back(
            std::make_unique<Striped_circle>(Point{x, y}, radius)
        );
        shapes[shapes.size() - 1].set_color(colors[i % colors.size()]);
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
    const std::string label = "Striped_circle";
    Simple_window win{Point{win_x, win_y}, win_width, win_height, label};

    // Properties
    constexpr int radius = 100;
    constexpr int spacing = 50;
    constexpr double frequency = 1;
    constexpr double amplitude = 0.65;
    std::array<Color, 2> colors = {{
                                    Color::black, Color::dark_cyan
    }};

    // Pattern
    Vector_ref<Striped_circle> striped_circles;
    generate_sine(striped_circles,
                  colors,
                  win_width,
                  win_height,
                  radius,
                  spacing,
                  frequency,
                  amplitude
    );
    for (Striped_circle* p : striped_circles)
        win.attach(*p);

    win.wait_for_button();
    win.close();
}
