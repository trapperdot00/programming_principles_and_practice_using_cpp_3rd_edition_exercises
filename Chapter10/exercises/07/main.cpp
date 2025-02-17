#include "PPP/Simple_window.h"
#include "PPP/Graph.h"

// Hold details about a straight line
// y = mx + b
struct Line_data {
    double slope;       // m
    int y_intercept;    // b
};

// Calculate line from two points touching the line
Line_data line_from_points(const Point& p1, const Point& p2) {
    int delta_x = p2.x - p1.x;
    int delta_y = p2.y - p1.y;
    double slope = double(delta_y) / delta_x;
    int y_intercept = p1.x * -slope + p1.y;
    return Line_data{slope, y_intercept};
}

// Substitute x back into the line,
// get y-value of a given x-position of a line
int get_y(const Line_data& line, int x) {
    return line.slope * x + line.y_intercept;
}

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
    constexpr int win_height = 800;

    // Create window
    const std::string label = "House";
    Simple_window win{Point{win_x, win_y}, win_width, win_height, label};

    // Global scale and offset
    constexpr double scale = 1;
    constexpr int x_offset = 0;
    constexpr int y_offset = 150;

    // Sizes
    constexpr int wall_width = 500 * scale;
    constexpr int wall_height = 400 * scale;
    constexpr int roof_height = 200 * scale;
    constexpr int door_width = 120 * scale;
    constexpr int door_height = 175 * scale;
    constexpr int window_width = 120 * scale;
    constexpr int window_height = 120 * scale;
    constexpr int chimney_width = 100 * scale;

    // Colors
    const Color wall_color = Color{212, 127, 127};
    const Color roof_color = Color{194, 165, 140};
    const Color door_color = Color{110, 100, 92};
    const Color window_color = Color{240, 247, 245};
    const Color chimney_color = Color::black;
    const Color smoke_color = Color{200, 200, 200};

    // Wall is centered to the window, and offset by a set amount
    constexpr int wall_x = (win_width - wall_width) / 2 + x_offset;
    constexpr int wall_y = (win_height - wall_height) / 2 + y_offset;

    // Create wall
    Rectangle wall{Point{wall_x, wall_y}, wall_width, wall_height};
    wall.set_fill_color(wall_color);

    // Roof: left and right points are in the same position
    // as the wall's top-left and top-right points,
    // the center point is offset vertically by height and
    // is horizontally centered between the two points
    Polygon roof;
    Point roof_left{wall_x, wall_y};
    Point roof_right{wall_x + wall_width, wall_y};
    Point roof_center{wall_x + wall_width / 2, wall_y - roof_height};
    roof.add(roof_left);
    roof.add(roof_right);
    roof.add(roof_center);
    roof.set_fill_color(roof_color);

    // Door: centered horizontally between wall's left and right x-coordinates
    constexpr int door_x = wall_x + (wall_width - door_width) / 2;
    constexpr int door_y = wall_y + wall_height - door_height;
    Rectangle door{Point{door_x, door_y}, door_width, door_height};
    door.set_fill_color(door_color);

    // Left window: horizontally centered to the left third of the house,
    // vertically centered between the door and the wall
    constexpr int left_window_x = wall_x + wall_width / 4 - window_width / 2;
    constexpr int left_window_y = (wall_y + door_y - window_height) / 2;
    Rectangle left_window{Point{left_window_x, left_window_y}, window_width, window_height};
    left_window.set_fill_color(window_color);

    // Left window: horizontally centered to the right third of the house,
    // vertically centered between the door and the wall
    constexpr int right_window_x = wall_x + wall_width * 3 / 4 - window_width / 2;
    constexpr int right_window_y = (wall_y + door_y - window_height) / 2;
    Rectangle right_window{Point{right_window_x, right_window_y}, window_width, window_height};
    right_window.set_fill_color(window_color);

    // Add splitting lines for windows
    constexpr int left_window_x_center = left_window_x + window_width / 2;
    constexpr int left_window_y_center = left_window_y + window_height / 2;
    Line left_window_vertical{Point{left_window_x_center, left_window_y}, Point{left_window_x_center, left_window_y + window_height}};
    Line left_window_horizontal{Point{left_window_x, left_window_y_center}, Point{left_window_x + window_width, left_window_y_center}};
    constexpr int right_window_x_center = right_window_x + window_width / 2;
    constexpr int right_window_y_center = right_window_y + window_height / 2;
    Line right_window_vertical{Point{right_window_x_center, right_window_y}, Point{right_window_x_center, right_window_y + window_height}};
    Line right_window_horizontal{Point{right_window_x, right_window_y_center}, Point{right_window_x + window_width, right_window_y_center}};

    // Line details of roof's top-left line, where the chimney will go
    Line_data roof_line = line_from_points(roof_left, roof_center);

    // Chimney: centered to the left roof-line
    constexpr int chimney_x = wall_x + wall_width / 4 - chimney_width / 2;
    // Get y-coordinates for the two chimney points that touch the roof
    const int chimney_down_y = get_y(roof_line, chimney_x);
    const int chimney_up_y = get_y(roof_line, chimney_x + chimney_width);

    // Create chimney
    Polygon chimney;
    chimney.add(Point{chimney_x, chimney_down_y});
    chimney.add(Point{chimney_x, chimney_up_y});
    chimney.add(Point{chimney_x + chimney_width, chimney_up_y});
    chimney.set_fill_color(chimney_color);

    // Create smoke: fixed to two points and the chimney's top horizontal center
    Polygon smoke;
    Point smoke_start = Point{chimney_x + chimney_width / 2, chimney_up_y};
    Point smoke_top_end = Point{30, 0};
    Point smoke_bottom_end = Point{200, 0};
    smoke.add(smoke_start);
    smoke.add(smoke_top_end);
    smoke.add(smoke_bottom_end);
    smoke.set_fill_color(smoke_color);
    smoke.set_color(smoke_color);

    // Paint objects to the window
    win.attach(wall);
    win.attach(roof);
    win.attach(door);
    win.attach(left_window);
    win.attach(left_window_vertical);
    win.attach(left_window_horizontal);
    win.attach(right_window);
    win.attach(right_window_vertical);
    win.attach(right_window_horizontal);
    win.attach(chimney);
    win.attach(smoke);

    win.wait_for_button();
}
