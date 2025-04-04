#include "PPP/Simple_window.h"
#include "PPP/Graph.h"

class Binary_tree : public Shape {
public:
    Binary_tree(Point c, int r, int levels) {
        const int y_step = 4 * r;
        const int x_step = y_step;
        int y = c.y;
        for (int i = 0; i < levels; ++i) {
            const int nodes = std::pow(2, i);
            // Make it symmetric
            int x = (i ? x_step / 2 : 0) + c.x - nodes / 2 * x_step;
            for (int j = 0; j < nodes; ++j) {
                if (i) {
                    int parent = nodes / 2 - 1 + j / 2;
                    l.add(n[parent].center(), Point{x, y});
                }
                n.push_back(std::make_unique<Circle>(Point{x, y}, r));
                x += x_step;
            }
            y += y_step;
        }
    }
    void draw_specifics(Painter &painter) const override {
        l.draw_specifics(painter);
        for (Circle* p : n)
            p->draw_specifics(painter);
    }
private:
    Lines l;                // Connecting lines
    Vector_ref<Circle> n;   // Nodes
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
    const std::string label = "Binary_tree";
    Simple_window win{Point{win_x, win_y}, win_width, win_height, label};

    Binary_tree bt{Point{400, 100}, 26, 4};
    bt.set_fill_color(Color::black);
    win.attach(bt);

    win.wait_for_button();
}
