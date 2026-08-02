#include "PPP/Window.h"
#include "PPP/Graph.h"
#include "PPP/GUI.h"
using namespace Graph_lib;

#include "Parameter_parser.hpp"
#include <string>
#include <cmath>
#include <functional>
#include <utility>
#include <vector>
#include <memory>
#include <optional>
#include <functional>

class Grapher_window : public Window
{
    static constexpr int pixels_per_notch = 32;
    enum class GraphFunc
    {
        sign,
        basic,
        abs,
        sine,
        cosine,
        log,
        sqrt,
    };
public:
    Grapher_window(Point xy, int w, int h, const std::string& title = "Grapher") :
        Window{xy, w, h, title},
        x_scale{static_cast<double>(w) / pixels_per_notch},
        y_scale{static_cast<double>(h) / pixels_per_notch},
        start_x{-x_scale / 2},
        end_x{x_scale / 2},
        x_axis(Axis::x, Point{0, h / 2}, w, w / pixels_per_notch),
        y_axis(Axis::y, Point{w / 2, h}, h, h / pixels_per_notch),
        add_new{Point{0, 0}, 75, 30, "Add new", [this] { show_expr_reader(); }},
        clear_all{Point{x_max() - 75, 0}, 75, 30, "Clear", [this] { remove_functions(); }},
        back_to_grapher{Point{x_max() - 75, 0}, 75, 30, "Back", [this] { show_grapher(); }},
        back_to_expr{Point{x_max() - 75, 0}, 75, 30, "Back", [this] { expr.reset(); show_expr_reader(); }},
        function_menu{Point{(x_max() - 150) / 2, 0}, 150, 75, Menu::vertical, "Functions"},
        expr_box{Point{0, 0}, 100, 50, "Parameter", [this] { read_expr(); }},
        error_box{Point{0, y_max() / 2}, "", Out_box::vertical}
    {
        attach(expr_box);
        attach(add_new);
        attach(clear_all);
        attach(back_to_grapher);
        attach(back_to_expr);
        attach(function_menu);
        function_menu.attach(std::make_unique<Button>(
            Point{0, 0}, 150, 50, "Sign", [this] { select_function(GraphFunc::sign); }
        ));
        function_menu.attach(std::make_unique<Button>(
            Point{0, 0}, 150, 50, "Basic f(x) = y", [this] { select_function(GraphFunc::basic); }
        ));
        function_menu.attach(std::make_unique<Button>(
            Point{0, 0}, 150, 50, "Absolute value", [this] { select_function(GraphFunc::abs); }
        ));
        function_menu.attach(std::make_unique<Button>(
            Point{0, 0}, 150, 50, "Sine", [this] { select_function(GraphFunc::sine); }
        ));
        function_menu.attach(std::make_unique<Button>(
            Point{0, 0}, 150, 50, "Cosine", [this] { select_function(GraphFunc::cosine); }
        ));
        function_menu.attach(std::make_unique<Button>(
            Point{0, 0}, 150, 50, "Log", [this] { select_function(GraphFunc::log); }
        ));
        function_menu.attach(std::make_unique<Button>(
            Point{0, 0}, 150, 50, "Square root", [this] { select_function(GraphFunc::sqrt); }
        ));
        error_box.data.set_color(Color::red);
        show_grapher();
    }
private:
    void hide_all()
    {
        detach(x_axis);
        detach(y_axis);
        std::for_each(functions.begin(), functions.end(),
            [this](auto& pf) { detach(*pf); }
        );
        add_new.hide();
        clear_all.hide();
        back_to_grapher.hide();
        back_to_expr.hide();
        function_menu.hide();
        expr_box.hide();
        detach(error_box);
    }
    void show_grapher()
    {
        hide_all();
        attach(x_axis);
        attach(y_axis);
        std::for_each(functions.begin(), functions.end(), [this](auto& pf) { attach(*pf); });
        add_new.show();
        clear_all.show();
    }
    void show_expr_reader()
    {
        hide_all();
        back_to_grapher.show();
        expr_box.show();
        attach(error_box);
        error_box.put("\n");
    }
    void show_function_selector()
    {
        hide_all();
        back_to_expr.show();
        function_menu.show();
    }
    void read_expr()
    {
        if (expr_box.last_result() == In_box::accepted)
        {
            std::istringstream is{expr_box.last_string_value()};
            try
            {
                expr = parser(is);
                show_function_selector();
            }
            catch (std::exception& e)
            {
                error_box.put(e.what());
            }
        }
    }
    void select_function(GraphFunc gf)
    {
        std::function<double(double)> func;
        switch (gf)
        {
            case GraphFunc::sign:
                func = [this](double x) {
                    double value = expr->evaluate(x);
                    if (value > 0)
                        return 1;
                    if (value < 0)
                        return -1;
                    return 0;
                };
                break;
            case GraphFunc::basic:
                func = [this](double x) { return expr->evaluate(x); };
                break;
            case GraphFunc::abs:
                func = [this](double x) { return std::abs(expr->evaluate(x)); };
                break;
            case GraphFunc::sine:
                func = [this](double x) { return std::sin(expr->evaluate(x)); };
                break;
            case GraphFunc::cosine:
                func = [this](double x) { return std::cos(expr->evaluate(x)); };
                break;
            case GraphFunc::log:
                func = [this](double x) { return std::log(expr->evaluate(x)); };
                break;
            case GraphFunc::sqrt:
                func = [this](double x) { return std::sqrt(expr->evaluate(x)); };
                break;
        }
        auto fwidget = std::make_unique<Function>(
            func, start_x, end_x, Point{x_max() / 2, y_max() / 2},
            x_max(), x_scale, y_scale
        );
        functions.push_back(std::move(fwidget));
        expr.reset();
        func_choice = std::nullopt;
        show_grapher();
    }
    void remove_functions()
    {
        std::for_each(functions.begin(), functions.end(), [this](auto& pf) { detach(*pf); });
        functions.clear();
    }
private:
    double x_scale;
    double y_scale;
    double start_x;
    double end_x;
    Parameter_parser parser;
    Axis x_axis;
    Axis y_axis;
    std::vector<std::unique_ptr<Function>> functions;
    Button add_new;
    Button clear_all;
    Button back_to_grapher;
    Button back_to_expr;
    Menu function_menu;
    In_box expr_box;
    Out_box error_box;
    std::shared_ptr<Expression> expr;
    std::optional<GraphFunc> func_choice;
};

int main(int /*argc*/, char* /*argv*/[])
{
    Application app;
    Grapher_window win{Point{200, 100}, x_max(), y_max()};
    app.gui_main();
}
