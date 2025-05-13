#include "PPP/Simple_window.h"
#include "PPP/Graph.h"

#include <chrono>

int month_to_int(const std::string& month) {
    static const std::vector<std::string> month_tbl = {
        "jan", "feb", "mar", "apr", "may", "jun",
        "jul", "aug", "sep", "oct", "nov", "dec"
    };
    int i = 0;
    while (i < int(month_tbl.size()) && month != month_tbl[i])
        ++i;
    if (i < 0 || 11 < i)
        throw std::runtime_error{"invalid month"};
    return i;
}

struct Reading {
    std::string location;
    std::vector<int> temps = std::vector<int>(12);
};

// Reallyyyyyy convoluted!
std::istream& operator>>(std::istream& is, Reading& r) {
    char ch1 = 0;
    char ch2 = 0;
    if (!(is >> ch1 >> ch2))
        return is;
    if (ch1 != '(' || ch2 != '"') {
        is.clear(std::ios_base::failbit);
        return is;
    }

    std::string location;
    char ch3 = 0;
    while (is.get(ch3) && ch3 != '"')
        location += ch3;
    if (!is)
        return is;
    if (ch3 != '"') {
        is.clear(std::ios_base::failbit);
        return is;
    }

    char ch4 = 0;
    if (!(is >> ch4))
        return is;
    if (ch4 != ':') {
        is.clear(std::ios_base::failbit);
        return is;
    }

    std::vector<int> temps(12);
    char ch5 = 0;
    while (is >> ch5 && ch5 == '(') {
        std::string month;
        char ch6 = 0;
        for (int i = 0; i < 3 && is.get(ch6); ++i)
            month += ch6;
        if (!is)
            return is;
        int month_num = month_to_int(month);

        char ch7 = 0;
        int temp = 0;
        char ch8 = 0;
        if (!(is >> ch7 >> temp >> ch8))
            return is;
        if (ch7 != ':' || ch8 != ')') {
            is.clear(std::ios_base::failbit);
            return is;
        }
        temps[month_num] = temp;
    }
    if (ch5 == ')') {
        r.location = location;
        r.temps = temps;
    }
    else
        is.clear(std::ios_base::failbit);
    return is;
}

int max_temp(const std::vector<Reading>& vec) {
    if (vec.empty())
        throw std::runtime_error{"empty vector"};
    std::vector<int>::const_iterator max = vec[0].temps.cend();
    for (const Reading& r : vec) {
        for (auto it = r.temps.cbegin(); it != r.temps.cend(); ++it) {
            if (max == vec[0].temps.cend() || *max < *it)
                max = it;
        }
    }
    if (max == vec[0].temps.cend())
        throw std::runtime_error{"no maximum"};
    return *max;
}

class Scale {
public:
    Scale(int cb, int vb, double s)
        : coord_base{cb}, value_base{vb}, scale{s}
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
    const std::string label = "Average maximum temperatures";

    constexpr int x_offset = 100;
    constexpr int x_space = 50;
    constexpr int x_length = win_width - x_offset - x_space;

    constexpr int y_offset = 50;
    constexpr int y_space = 50;
    constexpr int y_length = win_height - y_offset - y_space;

    constexpr Point bl{x_offset, win_height - y_offset};

    Simple_window win{Point{win_x, win_y}, win_width, win_height, label};

    const std::string filename = "../../data.txt";
    std::ifstream is{filename};
    if (!is)
        throw std::runtime_error{"can't open file " + filename};

    std::vector<Reading> vec;
    for (Reading r; is >> r; )
        vec.push_back(r);

    const int min_tmp = 0;
    const int max_tmp = max_temp(vec);

    constexpr int x_notch_n = 11;
    constexpr int y_notch_n = 5;

    constexpr double x_scale = double(x_length) / x_notch_n;
    const double y_scale = double(y_length) / (max_tmp - min_tmp);

    Scale xs{x_offset, 0, x_scale};
    Scale ys{win_height - y_offset, min_tmp, -y_scale};

    std::cout << min_tmp << '\t' << max_tmp << '\n' << x_scale << '\t' << y_scale << '\n';


    Axis xa{Axis::x, bl, x_length, x_notch_n,
            "0  jan  feb  mar  apr   may  jun  jul  aug   sep  oct  nov  dec"};
    xa.label.move(-170, 0);

    std::ostringstream ya_os;
    ya_os << "temperature in Celsius (1 notch == " << (max_tmp - min_tmp) / y_notch_n << ')';
    Axis ya{Axis::y, bl, y_length, y_notch_n, ya_os.str()};
    ya.label.move(0, -20);

    std::vector<std::unique_ptr<Open_polyline>> lines;
    for (const Reading& r : vec) {
        std::unique_ptr<Open_polyline> p = std::make_unique<Open_polyline>();
        for (int i = 0; i < int(r.temps.size()); ++i) {
            p->add(Point{xs(i), ys(r.temps[i])});
        }
        lines.push_back(std::move(p));
    }

    std::vector<std::unique_ptr<Text>> line_labels;
    std::default_random_engine e(std::chrono::steady_clock::now().time_since_epoch().count());
    std::uniform_int_distribution<int> u(0, 20);
    for (size_t i = 0; i < vec.size(); ++i) {
        Color col{u(e)};
        std::unique_ptr<Open_polyline>& p = lines[i];
        const auto [x, y] = p->point(0);
        line_labels.push_back(std::make_unique<Text>(Point{x - x_offset, y}, vec[i].location));
        p->set_style(Line_style(Line_style::solid, 4));
        p->set_color(col);
        win.attach(*p);
        win.attach(*line_labels.back());
    }
    win.attach(xa);
    win.attach(ya);
    win.wait_for_button();
}
