#include "PPP/Window.h"
#include "PPP/Graph.h"
#include "PPP/GUI.h"
using namespace Graph_lib;

#include <array>
#include <algorithm>
#include <memory>
#include <string>

class My_window : public Window
{
public:
    My_window(int w, int h, const std::string& title) :
        Window{w, h, title},
        quit{Point{w - 70, 0}, 70, 20, "Quit", [this]{ close(); }},
        next{Point{w - 70, 30}, 70, 20, "Next", []{}}
    {
        attach(quit);
        attach(next);
    }

    My_window(Point xy, int w, int h, const std::string& title) :
        Window{xy, w, h, title},
        quit{Point{w - 70, 0}, 70, 20, "Quit", [this]{ close(); }},
        next{Point{w - 70, 30}, 70, 20, "Next", []{}}
    {
        attach(quit);
        attach(next);
    }
private:
    Button quit;
    Button next;
};

class Checkerboard_window : public My_window
{
public:
    Checkerboard_window(int w, int h, const std::string& title) :
        My_window{w, h, title}
    {
        place_widgets();
    }
    Checkerboard_window(Point xy, int w, int h, const std::string& title) :
        My_window{xy, w, h, title}
    {
        place_widgets();
    }
private:
    void place_widgets()
    {
        int textbox_w = 300;
        int textbox_h = 200;
        textbox = std::make_unique<Out_box>(Point{x_max() - textbox_w, y_max() - textbox_h}, "Button pressed: ");
        textbox->put("none");
        int button_area_w = x_max() - textbox_w;
        int button_area_h = y_max();
        int cell_w = button_area_w / width;
        int cell_h = button_area_h / height;
        double w_scale = 1;
        double h_scale = 1;
        int w = w_scale * cell_w;
        int h = h_scale * cell_h;
        int x_pad = (cell_w - w) / 2;
        int y_pad = (cell_h - h) / 2;
        for (int row = 0; row < height; ++row)
        {
            for (int col = 0; col < width; ++col)
            {
                int x = x_pad + col * cell_w;
                int y = y_pad + row * cell_h;
                Point p{x, y};
                size_t i = row * height + col;
                buttons[i] = std::make_unique<Button>(p, w, h, std::to_string(i), [this, i]{ textbox->put(i); });
            }
        }
        std::for_each(buttons.begin(), buttons.end(), [this](auto& bp){ attach(*bp); });
        attach(*textbox);
    }
private:
    static constexpr int width = 4;
    static constexpr int height = 4;
    std::unique_ptr<Out_box> textbox;
    std::array<std::unique_ptr<Button>, width * height> buttons;
};

int main(int /*argc*/, char* /*argv*/[])
{
    Application app;
    Checkerboard_window win{x_max(), y_max(), "Checkerboard_window"};
    app.gui_main();
}
