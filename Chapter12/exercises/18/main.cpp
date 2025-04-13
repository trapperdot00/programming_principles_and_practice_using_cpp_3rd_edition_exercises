#include "PPP/Simple_window.h"
#include "PPP/Graph.h"

class Node : public Rectangle {
public:
    Node(Point tl, int ww, int hh, const std::string& txt)
        : Rectangle{tl, ww, hh}, t{tl, txt}
    {}
    void add_node(const std::string& txt) {
        if (find_node(txt) < c.size())
            throw std::runtime_error{"node with this label exists"};
        Point next = next_child_pos();
        c.push_back(std::make_unique<Node>(next, width(), height(), txt));
        connect_with(next);
    }
    void draw_specifics(Painter& painter) const override {
        Rectangle::draw_specifics(painter);
        t.draw_specifics(painter);
        draw_child_nodes(painter);
        l.draw_specifics(painter);
    }
    size_t child_node_count() const {
        return c.size();
    }
    Node& operator[](size_t i) {
        return *c[i];
    }
    void move(int dx, int dy) {
        Rectangle::move(dx, dy);
        t.move(dx, dy);
        for (std::unique_ptr<Node>& p : c)
            p->move(dx, dy);
    }
protected:
    void draw_child_nodes(Painter& painter) const {
        for (const std::unique_ptr<Node>& p : c)
            p->draw_specifics(painter);
    }
    Point next_child_pos() const {
        const Node* np = lowest_node();
        return Point{point(0).x + width(), np->point(0).y + np->height()};
    }
    // Return index of node, or index of size(), must check to avoid errors
    size_t find_node(const std::string& node_txt) {
        size_t i = 0;
        while (i < c.size() && node_txt != c[i]->t.label()) {
            ++i;
        }
        return i;
    }
    const Node* lowest_node() const {
        if (c.empty())
            return this;
        return c[c.size() - 1]->lowest_node();
    }
    void connect_with(Point p) {
        Point curr_bottom_mid{point(0).x + width() / 2, point(0).y + height()};
        Point midpoint1{point(0).x + width() / 2, p.y + height() / 2};
        Point midpoint2{midpoint1.x + width() / 2, midpoint1.y};
        l.add(curr_bottom_mid, midpoint1);
        l.add(midpoint1, midpoint2);
    }
private:
    Text t;
    std::vector<std::unique_ptr<Node>> c;  // Child nodes
    Lines l;    // Connecting lines
};

class Diagram : public Node {
public:
    Diagram(Point tl, int ww, int hh, const std::string& txt)
        : Node{tl, ww, hh, txt}
    {}
    void add_node_to(const std::string& parent_node_txt, const std::string& txt) {
        size_t node_index = find_node(parent_node_txt);
        if (node_index >= child_node_count())
            throw std::runtime_error{"node doesn't exist"};
        Node::operator[](node_index).add_node(txt);
        move_down_nodes_after(node_index);
    }
private:
    // Retain space, prevent overlapping after inserting node
    // before an existing node
    void move_down_nodes_after(size_t n) {
        for (size_t i = n + 1; i < child_node_count(); ++i) {
            Node &np = Node::operator[](i);
            np.move(0, np.height());
        }
    }
};

// Logical grouping
struct Hierarchy {
    size_t count() const {
        return children.size() + 1;
    }
    std::string parent;
    std::vector<std::string> children;
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
    const std::string label = "std::exception class hierarchy diagram";

    Simple_window win{Point{win_x, win_y}, win_width, win_height, label};

    const std::vector<Hierarchy> hierarchy = {
        {"std::logic_error", {
            {
                "std::domain_error",
                "std::invalid_argument",
                "std::length_error",
                "std::out_of_range"
            }
        }},
        {"std::runtime_error", {
            {
                "std::range_error",
                "std::overflow_error",
                "std::underflow_error"
            }
        }}
    };
    int i = 0;
    for (const Hierarchy& h : hierarchy)
        i += h.count();

    Diagram d{Point{0, 0}, int(std::ceil(win_width / 3.0)), win_height / (i + 1), "std::exception"};
    for (const Hierarchy& h : hierarchy) {
        d.add_node(h.parent);
        for (const std::string& c : h.children)
            d.add_node_to(h.parent, c);
    }

    d.set_fill_color(Color::yellow);
    d.set_style(Line_style{Line_style::solid, 2});
    win.attach(d);
    win.wait_for_button();
}
