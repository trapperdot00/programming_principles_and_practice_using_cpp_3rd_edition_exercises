#include "PPP/Simple_window.h"
#include "PPP/Graph.h"

class Bar_graph : public Shape {
public:
    Bar_graph(Point orig, int width, int height)
        : Shape{orig}, ww{width}, hh{height}
    {
        create_axis();
    }
    void add(double d) {
        handle_min(d);
        if (handle_max(d))
            create_axis();
        v.push_back(d);
        create_bars();
    }
    void draw_specifics(Painter& painter) const override {
        draw_bars(painter);
        draw_axis(painter);
    }
    double max() const { return max_v; }
    double min() const { return min_v; }
private:
    bool handle_max(double d) {
        if (v.empty() || max_v < d) {
            max_v = d;
            return true;
        }
        return false;
    }
    bool handle_min(double d) {
        if (v.empty() || min_v > d) {
            min_v = d;
            return true;
        }
        return false;
    }
    void draw_bars(Painter& painter) const {
        for (const std::unique_ptr<Rectangle>& p : r)
            p->draw_specifics(painter);
    }
    void draw_axis(Painter& painter) const {
        ya->draw_specifics(painter);
    }
    void create_axis() {
        ya = std::make_unique<Axis>(Axis::y, point(0), hh, max());
    }
    void create_bars() {
        r.clear();
        const int width = ww / v.size();
        int x = point(0).x;
        for (double d : v) {
            const int h = get_height(d);
            add_rectangle(Point{x, point(0).y - h}, width, h);
            x += width;
        }
    }
    int get_height(double d) const {
        return max_v == min_v ? hh : hh * d / max_v;
    }
    template <typename... Args>
    void add_rectangle(Args&&... args) {
        r.push_back(std::make_unique<Rectangle>(args...));
    }
    int ww;
    int hh;
    std::vector<double> v;
    double max_v = 0;
    double min_v = 0;
    std::vector<std::unique_ptr<Rectangle>> r;
    std::unique_ptr<Axis> ya;
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
    const std::string label = "Bar_graph";

    constexpr int x_offset = 20;
    constexpr int x_spacing = 20;
    constexpr int x_length = win_width - x_offset - x_spacing;

    constexpr int y_offset = 20;
    constexpr int y_spacing = 20;
    constexpr int y_length = win_height - y_offset - y_spacing;

    constexpr Point bl{x_offset, win_height - y_offset};

    Simple_window win{Point{win_x, win_y}, win_width, win_height, label};

    Bar_graph bargraph{bl, x_length, y_length};
    bargraph.set_fill_color(Color::cyan);

    for (double d : {9,17,13,8,14,12,19,11,7,15,18,19,11,6}) {
        bargraph.add(d);
    }

    win.attach(bargraph);
    win.wait_for_button();
}
