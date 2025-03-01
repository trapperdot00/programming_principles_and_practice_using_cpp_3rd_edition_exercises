#include "PPP/Simple_window.h"
#include "PPP/Graph.h"

int main(int /*argc*/, char * /*argv*/[])
{
    // Make Graph_lib's contents available implicitly without using its scope
    using namespace Graph_lib;

    // Initialize display engine
    Application app;

    // Create window
    constexpr int win_x = 200;
    constexpr int win_y = 100;
    const std::string label = "Picture";
    Simple_window win{Point{win_x, win_y}, x_max(), y_max(), label};

    Image img{Point{0,0}, "../../mountain.JPEG"};

    // Crop image
    img.set_mask(Point{400, 100}, x_max(), y_max());

    win.attach(img);
    win.wait_for_button();
}
