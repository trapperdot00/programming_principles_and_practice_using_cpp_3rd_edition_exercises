#include "PPP/Window.h"
#include "PPP/Graph.h"
#include "PPP/GUI.h"
using namespace Graph_lib;

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

int main(int /*argc*/, char* /*argv*/[])
{
    Application app;
    My_window win{x_max(), y_max(), "My_window"};
    app.gui_main();
}
