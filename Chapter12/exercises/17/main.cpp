#include "PPP/Simple_window.h"
#include "PPP/Graph.h"

class Controller {
public:
    virtual void on() = 0;
    virtual void off() = 0;
    virtual void set_level(int) = 0;
    virtual void show() const = 0;
};

class Controller_tester : public Controller {
public:
    void on() override {
        b = true;
    }
    void off() override {
        b = false;
    }
    void set_level(int level) override {
        l = level;
    }
    void show() const override {
        std::cout << (b ? "On" : "Off")
                  << ", level: "
                  << l
                  << '\n';
    }
private:
    bool b = false; // On/Off status
    int l = 0;  // Level
};

class Line_color_controller : public Controller {
public:
    Line_color_controller(Shape& shape) : s{shape} {}

    void on() override {
        b = true;
        draw();
    }
    void off() override {
        b = false;
        s.set_color(Color::invisible);
    }
    void set_level(int level) override {
        c = level;
        if (b)
            draw();
    }
    void show() const override {
        std::cout << (b ? "Visible" : "Invisible")
                  << ", color: "
                  << c
                  << '\n';
    }
private:
    void draw() {
        s.set_color(Color(c));
    }

    bool b = true; // On/Off visibility
    int c = 0;  // Color
    Shape& s;   // Controlled shape
};

class Fill_color_controller : public Controller {
public:
    Fill_color_controller(Shape& shape) : s{shape} {}
    void on() override {
        b = true;
        draw();
    }
    void off() override {
        b = false;
        s.set_fill_color(Color::invisible);
    }
    void set_level(int level) override {
        c = level;
        if (b)
            draw();
    }
    void show() const override {
        std::cout << (b ? "Visible" : "Invisible")
                  << ", color: "
                  << c
                  << '\n';
    }
private:
    void draw() {
        s.set_fill_color(c);
    }

    bool b = false;
    int c = 0;
    Shape& s;   // Controlled shape
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
    const std::string label = "Controller";

    Simple_window win{Point{win_x, win_y}, win_width, win_height, label};

    std::cout << "Controller_tester:\n";
    Controller_tester t;
    t.show();
    t.on();
    t.show();
    t.set_level(100);
    t.show();
    t.off();
    t.show();

    std::cout << "\nLine_color_controller:\n";
    Rectangle r{Point{(win_width - 400) / 2, (win_height - 300) / 2}, 400, 300};
    Line_color_controller rlc{r};
    rlc.show();
    rlc.set_level(10);
    rlc.show();
    rlc.off();
    rlc.show();
    rlc.on();
    rlc.show();

    std::cout << "\nFill_color_controller:\n";
    Fill_color_controller rfc{r};
    rfc.show();
    rfc.set_level(4);
    rfc.show();
    rfc.off();
    rfc.show();
    rfc.on();
    rfc.show();

    win.attach(r);
    win.wait_for_button();
}
