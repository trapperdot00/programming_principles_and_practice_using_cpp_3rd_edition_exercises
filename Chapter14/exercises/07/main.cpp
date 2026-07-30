#include "PPP/Window.h"
#include "PPP/Graph.h"
#include "PPP/GUI.h"
#include "PPP/Image_private.h"
using namespace Graph_lib;

#include <string>

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

class Plane_window : public Window
{
    static constexpr int frames_per_second = 60;
    static constexpr int millis_per_frame = 1000 / frames_per_second;
public:
    Plane_window(Point xy, int w, int h, const std::string& title = "Plane") :
        Window{xy, w, h, title},
        start_button{Point{w - 70, 0}, 70, 20, "Start", [this]{ start(); }},
        stop_button{Point{w - 70, 30}, 70, 20, "Stop", [this]{ stop(); }},
        img{xy, "../../plane.jpg"},
        velocity{8, 8}
    {
        attach(start_button);
        attach(stop_button);
        attach(img);
    }
private:
    bool plane_at_left_edge()
    {
        return img.point(0).x <= 0;
    }
    bool plane_at_right_edge()
    {
        return (img.point(0).x + img.width()) >= x_max();
    }
    bool plane_at_top_edge()
    {
        return img.point(0).y <= 0;
    }
    bool plane_at_bottom_edge()
    {
        return (img.point(0).y + img.height()) >= y_max();
    }
    void next_frame()
    {
        if (plane_at_left_edge() || plane_at_right_edge())
        {
            velocity.x *= -1;
        }
        if (plane_at_top_edge() || plane_at_bottom_edge())
        {
            velocity.y *= -1;
        }
        img.move(velocity.x, velocity.y);
    }
    void anim_loop()
    {
        if (playing)
        {
            next_frame();
            timer_wait(millis_per_frame, [this]{ anim_loop(); });
        }
    }
    void start()
    {
        if (!playing)
        {
            playing = true;
            anim_loop();
        }
    }
    void stop()
    {
        playing = false;
    }
private:
    Button start_button;
    Button stop_button;
    My_image img;
    struct Velocity
    {
        int x;
        int y;
    } velocity;
    bool playing = false;
};

int main(int /*argc*/, char* /*argv*/[])
{
    Application app;
    Plane_window win{Point{200, 100}, x_max(), y_max()};
    app.gui_main();
}
