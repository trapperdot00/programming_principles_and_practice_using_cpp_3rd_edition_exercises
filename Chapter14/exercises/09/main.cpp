#include "PPP/Window.h"
#include "PPP/Graph.h"
#include "PPP/GUI.h"
#include "PPP/Image_private.h"
using namespace Graph_lib;

#include <vector>
#include <string>
#include <utility>
#include <sstream>
#include <memory>

#include "Symbol_table.hpp"
#include "Calculator.hpp"

std::vector<std::string> splitlines(const std::string& s)
{
    std::vector<std::string> lines;
    std::string line;
    for (char c : s)
    {
        if (c == '\n')
        {
            lines.push_back(std::move(line));
            line = "";
        }
        else
        {
            line += c;
        }
    }
    if (!line.empty())
    {
        lines.push_back(std::move(line));
    }
    return lines;
}

class Calculator_window : public Window
{
public:
    Calculator_window(Point xy, int w, int h, const std::string& title = "Calculator") :
        Window{xy, w, h, title},
        inbox{Point{0, 0}, w, 50, "Expression", [this]{ calculate(); }},
        result_box{Point{0, h / 2}, "Result:", Out_box::vertical}
    {
        std::vector<std::string> lines = splitlines(calculator.usage());
        int y = 100;
        for (std::string& line : lines)
        {
            auto text = std::make_unique<Text>(Point{0, y}, line);
            text->set_font_size(18);
            usage_lines.push_back(std::move(text));
            y += 40;
        }
        attach(inbox);
        inbox.show();
        inbox.hide_buttons();
        for (const std::unique_ptr<Text>& t : usage_lines)
        {
            attach(*t);
        }
        result_box.label.set_font_size(18);
        result_box.data.set_font_size(18);
        attach(result_box);
    }
private:
    void calculate()
    {
        if (inbox.last_result() == In_box::accepted)
        {
            try
            {
                std::istringstream is{inbox.last_string_value() + ";"};
                double result = calculator(is);
                std::ostringstream os;
                os << result;
                result_box.put(os.str());
            }
            catch (...)
            {
                result_box.put("Invalid expression");
            }
        }
    }
private:
    Calculator calculator;
    In_box inbox;
    std::vector<std::unique_ptr<Text>> usage_lines;
    Out_box result_box;
};

int main(int /*argc*/, char* /*argv*/[])
{
    Application app;
    Calculator_window win{Point{200, 150}, x_max(), y_max()};
    app.gui_main();
}
