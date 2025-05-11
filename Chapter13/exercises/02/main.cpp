#include "PPP/Simple_window.h"
#include "PPP/Graph.h"

class Fcn : public Open_polyline {
public:
    Fcn(std::function<double(double)> f, double r1, double r2, Point orig,
        int count = 100, double xscale = 25, double yscale = 25)
    : fn{f}, rr1{r1}, rr2{r2}, op{orig}, cnt{count}, xscl{xscale}, yscl{yscale}
    {
        calculate_points();
    }
    void set_function(std::function<double(double)> f) {
        fn = f;
        calculate_points();
    }
    void set_range(double r1, double r2) {
        rr1 = r1;
        rr2 = r2;
        calculate_points();
    }

private:
    void calculate_points() {
        if (rr2 - rr1 <= 0)
            throw std::runtime_error{"invalid graphing range"};
        if (cnt <= 0)
            throw std::runtime_error{"non-positive graphing count"};
        double dist = (rr2 - rr1) / cnt;
        double r = rr1;
        for (int i = 0; i < cnt; ++i) {
            Point p{op.x + int(r *  xscl), op.y + int(fn(r) * yscl)};
            // We cannot delete points, only change them or add new ones
            if (i >= number_of_points())
                add(p);
            else
                set_point(i, p);
            r += dist;
        }
    }

    std::function<double(double)> fn;
    double rr1;
    double rr2;
    Point op;
    int cnt;
    double xscl;
    double yscl;
};

double slope(double x) {
    return -x;
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
    const std::string label = "Fcn";

    Simple_window win{Point{win_x, win_y}, win_width, win_height, label};

    constexpr int x_orig = win_width / 2;
    constexpr int y_orig = win_height / 2;
    constexpr Point orig{x_orig, y_orig};

    auto f = [](double d){ return std::sin(d); };
    auto f2 = [](double d){ return std::cos(d); };
    constexpr int r_min = -10;
    constexpr int r_max = 11;
    constexpr int n_points = 400;
    constexpr int x_scale = 40;
    constexpr int y_scale = 40;

    Fcn fn(f, r_min, r_max, orig, n_points, x_scale, y_scale);
    win.attach(fn);
    win.wait_for_button();
    win.detach(fn);

    fn.set_function(f2);
    fn.set_range(1, 2);
    win.attach(fn);
    win.wait_for_button();
    win.detach(fn);

    fn.set_function(slope);
    win.attach(fn);
    win.wait_for_button();
    win.detach(fn);

    fn.set_function(f);
    fn.set_range(r_min, r_max);
    win.attach(fn);
    win.wait_for_button();
}
