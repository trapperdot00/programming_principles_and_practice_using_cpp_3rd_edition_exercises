#include "PPP/Window.h"
#include "PPP/Graph.h"
#include "PPP/GUI.h"
#include "PPP/Image_private.h"
using namespace Graph_lib;

#include <string>
#include <vector>
#include <filesystem>
#include <fstream>
#include <sstream>
#include <optional>
#include <utility>
#include <set>

struct Conversion_rate
{
    std::string source;
    std::string target;
    double rate;
};

std::optional<Conversion_rate> parse_rate(const std::string& s)
{
    Conversion_rate convrate;
    char slash;
    std::istringstream is{s};
    if ((is >> convrate.source >> slash >> convrate.target >> convrate.rate) && (slash == '/'))
    {
        return convrate;
    }
    return std::nullopt;
}

using Convrates = std::vector<Conversion_rate>;

Convrates parse_rates(std::istream& is)
{
    Convrates rates;
    for (std::string line; std::getline(is, line); )
    {
        std::optional<Conversion_rate> convrate = parse_rate(line);
        if (convrate)
        {
            rates.push_back(std::move(*convrate));
        }
    }
    return rates;
}

Convrates rates_from_file(const std::filesystem::path& path)
{
    if (!std::filesystem::exists(path))
    {
        throw std::invalid_argument{"file '" + path.string() + "' doesn't exist"};
    }
    if (!std::filesystem::is_regular_file(path))
    {
        throw std::invalid_argument{"file '" + path.string() + "' is not a regular file"};
    }
    std::ifstream is{path.string()};
    return parse_rates(is);
}

class Currency_converter_window : public Window
{
public:
    Currency_converter_window(Convrates rates, Point xy, int w, int h, const std::string& title = "Currency converter") :
        Window{xy, w, h, title},
        convrates{std::move(rates)},
        source_menu{Point{0, 0}, w, h / 10, Menu::horizontal, "From"},
        source_label{Point{0, h / 10}, "Source currency"},
        target_menu{Point{0, y_max() - h / 10}, w, h / 10, Menu::horizontal, "To"},
        target_label{Point{0, y_max() - h / 10 - 24}, "Target currency"},
        inbox{Point{0, y_max() / 2 - 40}, 200, 40, "Amount", [this]{ select_amount(); }},
        outbox{Point{x_max() / 4, y_max() / 2}, "", Out_box::vertical}
    {
        std::set<std::string> sources;
        std::set<std::string> targets;
        for (const auto& convrate : convrates)
        {
            sources.insert(convrate.source);
            targets.insert(convrate.target);
        }
        for (const auto& source : sources)
        {
            source_menu.attach(std::make_unique<Button>(Point{0, 0}, 0, 0, source, [this, source]{ select_source_currency(source); }));
        }
        for (const auto& target : targets)
        {
            target_menu.attach(std::make_unique<Button>(Point{0, 0}, 0, 0, target, [this, target]{ select_target_currency(target); }));
        }
        attach(source_menu);
        attach(source_label);
        attach(target_menu);
        attach(target_label);
        attach(inbox);
        inbox.show();
        inbox.hide_buttons();
        attach(outbox);
        outbox.data.set_font(Font::helvetica);
        outbox.data.set_font_size(18);
        update_outbox();
    }
private:
    void select_source_currency(const std::string& source)
    {
        if (!source_currency || *source_currency != source)
        {
            source_currency = source;
            update_outbox();
        }
    }
    void select_target_currency(const std::string& target)
    {
        if (!target_currency || *target_currency != target)
        {
            target_currency = target;
            update_outbox();
        }
    }
    void select_amount()
    {
        if (inbox.last_result() == In_box::accepted)
        {
            std::istringstream is{inbox.last_string_value()};
            if (double tmp; is >> tmp)
            {
                amount = tmp;
                update_outbox();
            }
        }
    }
    std::optional<double> convert()
    {
        if (*source_currency == *target_currency)
        {
            return amount;
        }
        auto convrate = std::find_if(
            convrates.cbegin(), convrates.cend(),
            [this](const Conversion_rate& rate){
                return rate.source == *source_currency
                    && rate.target == *target_currency;
            });
        if (convrate == convrates.cend())
        {
            return std::nullopt;
        }
        return amount * convrate->rate;
    }
    void update_outbox()
    {
        std::ostringstream os;
        os << amount << ' '
           << (source_currency ? *source_currency : "?") << " to "
           << (target_currency ? *target_currency : "?");
        if (all_provided())
        {
            if (std::optional<double> converted = convert(); converted)
            {
                os << " = " << *converted;
            }
            else
            {
                os << " (no defined conversion)";
            }
        }
        outbox.put(os.str());
    }
    bool all_provided()
    {
        return source_currency && target_currency;
    }
private:
    Convrates convrates;
    Menu source_menu;
    Text source_label;
    Menu target_menu;
    Text target_label;
    double amount = 0;
    std::optional<std::string> source_currency;
    std::optional<std::string> target_currency;
    In_box inbox;
    Out_box outbox;
};

int main(int /*argc*/, char* /*argv*/[])
{
    Application app;
    Convrates convrates = rates_from_file("../../convrates.txt");
    Currency_converter_window win{convrates, Point{200, 100}, x_max(), y_max()};
    app.gui_main();
}
