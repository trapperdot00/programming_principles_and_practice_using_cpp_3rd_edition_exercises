#include "PPP/Window.h"
#include "PPP/Graph.h"
#include "PPP/GUI.h"
#include "PPP/Image_private.h"
using namespace Graph_lib;

#include <string>
#include <chrono>
#include <sstream>
#include <thread>
#include <cmath>
#include <numbers>

Point center(int w, int h)
{
    return Point{w / 2, h / 2};
}

double to_radians(double deg)
{
    return deg * std::numbers::pi_v<double> / 180;
}

class Clock_window : Window
{
public:
    Clock_window(Point xy, int w, int h, const std::string& title = "Clock") :
        Window{xy, w, h, title},
        circle{center(w, h), std::min(w / 2, h / 2) * 3 / 4},
        hour_hand_length{circle.radius() / 2},
        minute_hand_length{circle.radius() * 3 / 4},
        second_hand_length{circle.radius() * 5 / 6}
    {
        circle.set_style(Line_style{Line_style::solid, 4});
        attach(circle);
        next_frame();
    }
private:
    static auto get_time()
    {
        auto t = std::chrono::system_clock::now();
        auto zt = std::chrono::zoned_time{std::chrono::current_zone(), t};
        auto lt = zt.get_local_time();
        auto h = std::chrono::floor<std::chrono::days>(lt);
        auto time = std::chrono::hh_mm_ss{lt - h};
        return time;
    }
    std::unique_ptr<Line> make_hand(Point p)
    {
        return std::make_unique<Line>(circle.center(), p);
    }
    Point hand_point(int hand_length, double rads)
    {
        return Point{
            static_cast<int>(circle.center().x + hand_length * std::cos(rads)),
            static_cast<int>(circle.center().y + hand_length * std::sin(rads))
        };
    }
    static double hour_rads(int hours, int minutes, int seconds)
    {
        double deg = hours % 12 * 30 + minutes * (30.0 / 60.0) + seconds * (30.0 / 60.0 / 60.0) - 90;
        return to_radians(deg);
    }
    static double minute_rads(int minutes, int seconds)
    {
        double deg = minutes * 6 + seconds * (6.0 / 60.0) - 90;
        return to_radians(deg);
    }
    static double second_rads(int seconds)
    {
        double deg = seconds * 6 - 90;
        return to_radians(deg);
    }
    void change_hand(std::unique_ptr<Line>& hand, std::unique_ptr<Line> new_hand)
    {
        if (hand)
        {
            detach(*hand);
        }
        hand = std::move(new_hand);
        if (hand)
        {
            attach(*hand);
        }
    }
    void make_hour_hand(int hours, int minutes, int seconds)
    {
        change_hand(hour_hand, make_hand(hand_point(hour_hand_length, hour_rads(hours, minutes, seconds))));
        hour_hand->set_style(Line_style{Line_style::solid, 2});
    }
    void make_minute_hand(int minutes, int seconds)
    {
        change_hand(minute_hand, make_hand(hand_point(minute_hand_length, minute_rads(minutes, seconds))));
        minute_hand->set_style(Line_style{Line_style::solid, 2});
    }
    void make_second_hand(int seconds)
    {
        change_hand(second_hand, make_hand(hand_point(second_hand_length, second_rads(seconds))));
        second_hand->set_color(Color::red);
    }
    void make_hands()
    {
        auto time = get_time();
        int hours = time.hours().count();
        int minutes = time.minutes().count();
        int seconds = time.seconds().count();
        make_hour_hand(hours, minutes, seconds);
        make_minute_hand(minutes, seconds);
        make_second_hand(seconds);
    }
    void next_frame()
    {
        make_hands();
        timer_wait(1000, [this]{ next_frame(); });
    }
private:
    Circle circle;
    const int hour_hand_length;
    const int minute_hand_length;
    const int second_hand_length;
    std::unique_ptr<Line> hour_hand;
    std::unique_ptr<Line> minute_hand;
    std::unique_ptr<Line> second_hand;
};

int main(int /*argc*/, char* /*argv*/[])
{
    Application app;
    Clock_window win{Point{200, 200}, x_max(), y_max()};
    app.gui_main();
}
