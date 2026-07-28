#include "PPP/Window.h"
#include "PPP/Graph.h"
#include "PPP/GUI.h"
#include "PPP/Image_private.h"
using namespace Graph_lib;

#include <string>
#include <random>
#include <cassert>

inline int rand_int(int min, int max)
{
    static std::default_random_engine ran;
    return std::uniform_int_distribution<>{min, max}(ran);
}

class My_image : public Image
{
public:
    using Image::Image;
    int width() const
    {
        return get_impl().image.width();
    }
    int height() const
    {
        return get_impl().image.height();
    }
};

inline Point point_add_y(Point p, int dy)
{
    return Point{p.x, p.y + dy};
}

inline Point point_add(Point p, int dx, int dy)
{
    return Point{p.x + dx, p.y + dy};
}

class Image_window : public Window
{
public:
    Image_window(Point xy, int w, int h, const std::string& title) :
        Window{xy, w, h, title},
        topleft{w / 2, h / 2},
        img{topleft, "../../cat.png"},
        but{point_add_y(topleft, img.height()), img.width(), 20, "meow", [this]{ next_pos(); }}
    {
        attach(img);
        attach(but);
    }
private:
    void next_pos()
    {
        int dx = rand_int(-topleft.x, x_max() - topleft.x - widgets_width());
        int dy = rand_int(-topleft.y, y_max() - topleft.y - widgets_height());
        move_widgets(dx, dy);
    }
    void move_widgets(int dx, int dy)
    {
        topleft = point_add(topleft, dx, dy);
        img.move(dx, dy);
        but.move(dx, dy);
    }
    int widgets_width()
    {
        assert(img.width() == but.width);
        return img.width();
    }
    int widgets_height()
    {
        return img.height() + but.height;
    }
private:
    Point topleft;
    My_image img;
    Button but;
};

int main(int /*argc*/, char* /*argv*/[])
{
    Application app;
    Image_window win{Point{0, 0}, x_max(), y_max(), "Image + Button"};
    app.gui_main();
}
