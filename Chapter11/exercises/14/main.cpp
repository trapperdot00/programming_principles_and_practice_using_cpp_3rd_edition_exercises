#include "PPP/Simple_window.h"
#include "PPP/Graph.h"

// Inherit from Closed_polyline, we are sure that
// there will be no intersecting lines
struct Regular_hexagon : public Closed_polyline {
    Regular_hexagon(const Point& center, int distance) {
        // Whole circle: 360°
        constexpr double full_circle = 2 * M_PI;
        // Start at the top (90° angle)
        double angle = 0.5 * M_PI;
        // Increment by 60° each step
        double step = full_circle / 6;
        for (int i = 0; i < 6; ++i, angle += step) {
            // Basic trigonometry, get offsets from center
            int delta_x = distance * std::cos(angle);
            int delta_y = distance * std::sin(angle);
            // Get absolute coordinates
            int x = center.x + delta_x;
            int y = center.y + delta_y;
            Point p{x, y};
            Closed_polyline::add(p);
        }
    }
};

enum class TileDirection {
    RIGHT = 1, TOP_RIGHT, TOP_LEFT, LEFT, BOTTOM_LEFT, BOTTOM_RIGHT
};

int to_int(TileDirection t) {
    return static_cast<int>(t);
}

TileDirection to_tile_direction(int i) {
    if (i < to_int(TileDirection::RIGHT) || to_int(TileDirection::BOTTOM_RIGHT) < i)
        throw std::runtime_error{"out of range"};
    return TileDirection{i};
}

TileDirection& operator++(TileDirection& t) {
    t = (t == TileDirection::BOTTOM_RIGHT) ? TileDirection::RIGHT : TileDirection{to_int(t)+1};
    return t;
}

// Place Regular_hexagons next to each other in a given direction
// Modifies given Point to be the last placed hexagon's center
void place_n_hex
(Vector_ref<Regular_hexagon>& vec, Point& center, int distance, TileDirection direction, int n) {
    for (int i = 0; i < n; ++i) {
        // The distance between the current and the next hexagon's center
        double c = 2 * distance * std::cos(0.5 * M_PI / 3);
        // Angle that points to the given side's halfpoint, right to the next center
        double angle = (30 + to_int(direction) * 60) * M_PI / 180;
        // Calculate offset
        int dx = c * std::sin(angle);
        int dy = c * std::cos(angle);
        // Calculate absolute coordinates
        int x = center.x + dx;
        int y = center.y + dy;
        Point p{x,y};
        vec.push_back(std::make_unique<Regular_hexagon>(p, distance));
        // Set previous to current
        center.x = x;
        center.y = y;
    }
}

// Generate a grid of hexagons into a vector, with a specified width, height,
// and a starting point of center
// Given center is the top-left hexagon's position
void place_hex_grid
(Vector_ref<Regular_hexagon>& vec, Point center, int distance, int width, int height) {
    if (width < 1 || height < 1)
        throw std::runtime_error{"invalid grid size"};
    // Place first hexagon under the given point
    vec.push_back(std::make_unique<Regular_hexagon>(center, distance));
    for (int i = 0; i < height; ++i) {
        if (i) {    // Determine next row's first hexagon's position
            TileDirection connector = (i % 2 == 0) ? TileDirection::BOTTOM_LEFT : TileDirection::BOTTOM_RIGHT;
            place_n_hex(vec, center, distance, connector, 1);
        }
        TileDirection direction = (i % 2) ? TileDirection::LEFT : TileDirection::RIGHT;
        place_n_hex(vec, center, distance, direction, width - 1);
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
    constexpr int win_width = 600;
    constexpr int win_height = 600;
    const std::string label = "Hexagon tiling";
    Simple_window win{Point{win_x, win_y}, win_width, win_height, label};

    constexpr int radius = 60;
    constexpr int hex_width = 2 * std::tan(M_PI / 3) * 30;
    constexpr int hex_height = 2 * radius;
    constexpr int columns = 2 + win_width / hex_width;
    constexpr int rows = 3 + win_height / hex_height;

    Vector_ref<Regular_hexagon> vec;
    place_hex_grid(vec, Point{0, 0}, radius, columns, rows);

    for (Regular_hexagon* p : vec)
        win.attach(*p);

    win.wait_for_button();
}
