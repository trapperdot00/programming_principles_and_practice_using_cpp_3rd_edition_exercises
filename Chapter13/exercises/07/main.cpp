#include "PPP/Simple_window.h"
#include "PPP/Graph.h"

#include <chrono>

class Bar_graph : public Shape {
public:
    Bar_graph(Point orig, int width, int height, const std::string& text = "")
        : Shape{orig}, ww{width}, hh{height}, gl{orig, text}
    {
        create_axis();
    }
    void add(double d) {
        handle_min(d);
        const int prev_max = max_v;
        if (handle_max(d)) {
            create_axis();
            adjust_bar_label_heights(prev_max);
        }
        v.push_back(d);
        create_bars();
        shift_bar_labels();
        add_bar_label();
    }
    void draw_specifics(Painter& painter) const override {
        draw_bars(painter);
        draw_axis(painter);
        draw_graph_label(painter);
        draw_bar_labels(painter);
    }
    double max() const { return max_v; }
    double min() const { return min_v; }
    size_t bar_count() const { return r.size(); }

    std::string label() const {
        return gl.label();
    }
    void set_label(const std::string& text) {
        gl.set_label(text);
    }

    std::string bar_label(int index) const {
        return bl.at(index)->label();
    }
    void set_bar_label(int index, const std::string& text) {
        bl.at(index)->set_label(text);
    }

    void set_fill_color(Color col) {
        for (std::unique_ptr<Rectangle>& p : r)
            p->set_fill_color(col);
    }
    void set_bar_fill_color(size_t i, Color col) {
        r[i]->set_fill_color(col);
    }
    void set_bar_color(size_t i, Color col) {
        r[i]->set_color(col);
    }
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
            p->draw(painter);
    }
    void draw_axis(Painter& painter) const {
        ya->draw_specifics(painter);
    }
    void draw_graph_label(Painter& painter) const {
        gl.draw_specifics(painter);
    }
    void draw_bar_labels(Painter& painter) const {
        for (const std::unique_ptr<Text>& p : bl)
            p->draw_specifics(painter);
    }

    void create_axis() {
        ya = std::make_unique<Axis>(Axis::y, point(0), hh, max());
    }
    void create_bars() {
        r.clear();
        const int width = bar_width();
        int x = point(0).x;
        for (double d : v) {
            const int h = bar_height(d);
            add_rectangle(Point{x, point(0).y - h}, width, h);
            x += width;
        }
    }

    void add_bar_label(const std::string& text = "a") {
        if (v.empty())
            return;
        const int dx = (v.size() - 1) * bar_width();
        const Point p{point(0).x + dx, point(0).y - bar_height(v.back())};
        bl.push_back(std::make_unique<Text>(p, text));
    }
    void shift_bar_labels() {
        const int width = bar_width();
        for (size_t i = 1; i < bl.size(); ++i) {
            const int x = bl[i]->point(0).x;
            const int rel_x = point(0).x - x;
            const int dx = rel_x + i * width;
            bl[i]->move(dx, 0);
        }
    }
    void adjust_bar_label_heights(int prev_max) {
        if (max_v == 0)
            return;
        const double scale = double(prev_max) / max_v;
        for (size_t i = 0; i < bl.size(); ++i) {
            const int y = bl[i]->point(0).y;
            const int rel_y = point(0).y - y;
            const int dy = rel_y * scale - rel_y;
            bl[i]->move(0, -dy);
        }
    }

    int bar_width() const {
        return ww / v.size();
    }

    int bar_height(double d) const {
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
    // Graph label
    Text gl;
    // Bar labels
    std::vector<std::unique_ptr<Text>> bl;
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
    const std::string label = "Bar_graph with labels and colors";

    constexpr int x_offset = 100;
    constexpr int x_spacing = 100;
    constexpr int x_length = win_width - x_offset - x_spacing;

    constexpr int y_offset = 100;
    constexpr int y_spacing = 100;
    constexpr int y_length = win_height - y_offset - y_spacing;

    constexpr Point bl{x_offset, win_height - y_offset};

    Simple_window win{Point{win_x, win_y}, win_width, win_height, label};

    const std::string bglabel = "Random generated numbers";
    Bar_graph bargraph{bl, x_length, y_length, bglabel};

    constexpr size_t num_count = 8;

    std::vector<double> numbers;
    std::default_random_engine e(std::chrono::steady_clock::now().time_since_epoch().count());
    std::uniform_real_distribution<double> u(1, 10);
    for (size_t i = 0; i < num_count; ++i)
        numbers.push_back(u(e));

    for (size_t i = 0; i < numbers.size(); ++i) {
        std::ostringstream os;
        os << std::setprecision(2) << numbers[i];
        bargraph.add(numbers[i]);
        bargraph.set_bar_label(i, os.str());
    }

    std::uniform_int_distribution<int> col_u(1, 30);
    for (size_t i = 0; i < bargraph.bar_count(); ++i) {
        Color col{col_u(e)};
        bargraph.set_bar_fill_color(i, col);
        bargraph.set_bar_color(i, col);
    }
    win.attach(bargraph);
    win.wait_for_button();
}
