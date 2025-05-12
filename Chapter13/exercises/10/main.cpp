#include "PPP/Simple_window.h"
#include "PPP/Graph.h"

struct Reading {
    int population;
    int square_km;
};

bool population_comp(const Reading& r1, const Reading& r2) {
    return r1.population < r2.population;
}

bool square_km_comp(const Reading& r1, const Reading& r2) {
    return r1.square_km < r2.square_km;
}

std::istream& operator>>(std::istream& is, Reading& r) {
    char ch1 = 0;
    char ch2 = 0;
    char ch3 = 0;
    Reading tmp;
    if (is >> ch1 >> tmp.population >> ch2 >> tmp.square_km >> ch3) {
        if (ch1 == '(' && ch2 == ',' && ch3 == ')')
            r = tmp;
        else
            is.clear(std::ios_base::failbit);
    }
    return is;
}

class Scale {
public:
    Scale(int c, int v, double s)
        : coord_base{c}, value_base{v}, scale{s}
    {}
    int operator()(double d) const {
        return coord_base + (d - value_base) * scale;
    }
private:
    int coord_base;
    int value_base;
    double scale;
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
    const std::string label = "Country population per square kilometers";

    constexpr int x_offset = 50;
    constexpr int x_spacing = 50;
    constexpr int x_length = win_width - x_offset - x_spacing;

    constexpr int y_offset = 50;
    constexpr int y_spacing = 50;
    constexpr int y_length = win_height - y_offset - y_spacing;

    constexpr Point bl{x_offset, win_height - y_offset};

    Simple_window win{Point{win_x, win_y}, win_width, win_height, label};

    const std::string filename = "../../data.txt";
    std::ifstream is{filename};
    if (!is)
        throw std::runtime_error{"can't open file " + filename};

    std::vector<Reading> vec;
    for (Reading r; is >> r; )
        vec.push_back(r);

    const int min_population = 0;
    const int max_population = std::max_element(vec.cbegin(), vec.cend(), population_comp)->population;
    const int min_square_km = 0;
    const int max_square_km = std::max_element(vec.cbegin(), vec.cend(), square_km_comp)->square_km;
    const double x_scale = double(x_length) / (max_population - min_population);
    const double y_scale = double(y_length) / (max_square_km - min_square_km);
    Scale xs{x_offset, min_population, x_scale};
    Scale ys{win_height - y_offset, min_square_km, -y_scale};
    constexpr int notch_count = 10;

    std::ostringstream xa_os;
    xa_os << "population (1 notch == " << max_population / notch_count / 1'000'000 << "M)";
    Axis xa{Axis::x, bl, x_length, notch_count, xa_os.str()};
    xa.label.move(-40, 0);

    std::ostringstream ya_os;
    ya_os << "square kilometers (1 notch == " << max_square_km / notch_count / 1'000 << "K km2)";
    Axis ya{Axis::y, bl, y_length, notch_count, ya_os.str()};
    ya.label.move(-40, -20);

    Marks m("x");
    for (const Reading& r : vec) {
        m.add(Point{xs(r.population), ys(r.square_km)});
    }

    win.attach(xa);
    win.attach(ya);
    win.attach(m);
    win.wait_for_button();
}
