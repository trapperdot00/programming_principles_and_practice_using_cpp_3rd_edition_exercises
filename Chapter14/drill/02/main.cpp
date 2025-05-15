#include "PPP/GUI.h"

using namespace Graph_lib;

class Lines_window : public Window {
public:
    Lines_window(Application& app, Point p, int w, int h, const std::string& title)
    :   Window{p, w, h, title},
        app_p{&app},
        quit_button{Point{w - 70, 0}, 70, 20, "quit", [this]{ quit(); }},
        next_xy{Point{250, 0}, 50, 20, "next xy:", [this]{ next(); }},
        xy_out{Point{10, 10}, "current (x,y): "}
    {
        attach(lines);
        attach(quit_button);

        next_xy.hide_buttons();
        attach(next_xy);
        next_xy.show();

        xy_out.label.set_font_size(8);
        xy_out.data.set_font_size(8);
        attach(xy_out);
    }
private:
    void next() {
        if (next_xy.last_result() == In_box::accepted) {
            std::string s = next_xy.last_string_value();
            std::istringstream is{s};
            int x = 0;
            char ch = 0;
            int y = 0;
            if ((is >> x >> ch >> y) && (ch == ';' || ch == ',')) {
                lines.add(Point{x, y});
                std::ostringstream os;
                os << '(' << x << ';' << y << ')';
                xy_out.put(os.str());
            }
        }
        next_xy.clear_last_result();
    }
    void quit() {
        end_button_wait();
        next_xy.dismiss();
        app_p->quit();
    }
public:
    Open_polyline lines;
private:
    Application* app_p = nullptr;
    Button quit_button;
    In_box next_xy;
    Out_box xy_out;
};

int main() try {
    Application app;
    Lines_window win(app, {100, 100}, 600, 400, "lines");
    app.gui_main();
} catch (const std::exception& e) {
    std::cerr << "Exception: " << e.what() << '\n';
    return 1;
} catch (...) {
    std::cerr << "Other exception\n";
    return 2;
}
