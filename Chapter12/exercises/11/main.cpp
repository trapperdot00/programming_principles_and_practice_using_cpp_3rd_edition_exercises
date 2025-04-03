#include "PPP/Simple_window.h"
#include "PPP/Graph.h"

class Group {
public:
    void add(Shape& s) {
        vec.push_back(s);
    }
    void add(std::unique_ptr<Shape> p) {
        vec.push_back(std::move(p));
    }
    void move(size_t i, int dx, int dy) {
        vec[i].move(dx, dy);
    }
    void set_color(size_t i, Color c) {
        vec[i].set_color(c);
    }
    void set_style(size_t i, Line_style s) {
        vec[i].set_style(s);
    }
    void set_fill_color(size_t i, Color c) {
        vec[i].set_fill_color(c);
    }
    void attach_to(Window& w) {
        for (Shape* p : vec)
            w.attach(*p);
    }
    Point point(size_t i, int j) {
        return vec[i].point(j);
    }
    int size() const { return vec.size(); }
private:
    Vector_ref<Shape> vec;
};

void create_board(Group& g, Point tl, int columns, int rows, int tile_width, int tile_height, Color c1, Color c2) {
    for (int row = 0; row < rows; ++row) {
        int y = tl.y + row * tile_height;
        for (int column = 0; column < columns; ++column) {
            const int i = row * columns + column;
            int x = tl.x + column * tile_width;
            g.add(std::make_unique<Rectangle>(Point{x, y}, tile_width, tile_height));
            // Add color
            if (row % 2 == column % 2) {
                g.set_fill_color(i, c1);
            } else {
                g.set_fill_color(i, c2);
            }
        }
    }
}

void add_top_pieces(Group& board, int columns, int tile_width, int tile_height, Color col) {
    const int radius = std::min(tile_width, tile_height) * 2 / 5;
    for (int i = 0, cnt = 0; i < board.size() && cnt < 12; ++i) {
        Point tl = board.point(i, 0);
        Point p{tl.x + tile_width / 2, tl.y + tile_height / 2};
        int column = i % columns;
        int row = i / columns;
        if (row % 2 == column % 2) {
            board.add(std::make_unique<Circle>(p, radius));
            board.set_fill_color(board.size() - 1, col);
            ++cnt;
        }
    }
}

void add_bottom_pieces(Group& board, int columns, int rows, int tile_width, int tile_height, Color col) {
    const int radius = std::min(tile_width, tile_height) * 2 / 5;
    for (int i = rows * columns - 1, cnt = 0; i >= 0 && cnt < 12; --i) {
        Point tl = board.point(i, 0);
        Point p{tl.x + tile_width / 2, tl.y + tile_height / 2};
        int column = i % columns;
        int row = i / columns;
        if (row % 2 == column % 2) {
            board.add(std::make_unique<Circle>(p, radius));
            board.set_fill_color(board.size() - 1, col);
            ++cnt;
        }
    }
}

void add_pieces(Group& board, int columns, int rows, int tile_width, int tile_height, Color c1, Color c2) {
    add_top_pieces(board, columns, tile_width, tile_height, c1);
    add_bottom_pieces(board, columns, rows, tile_width, tile_height, c2);
}

void checkerboard(Group& g, Point tl, int tile_width, int tile_height, Color c1, Color c2, Color c3, Color c4) {
    constexpr int columns = 8;
    constexpr int rows = 8;
    create_board(g, tl, columns, rows, tile_width, tile_height, c1, c2);
    add_pieces(g, columns, rows, tile_width, tile_height, c3, c4);
}

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
    const std::string label = "Group";
    Simple_window win{Point{win_x, win_y}, win_width, win_height, label};

    constexpr int tile_width = std::min(win_width, win_height) / 8;
    constexpr int tile_height = std::min(win_width, win_height) / 8;
    Point tl{
        (win_width - tile_width * 8) / 2,
        (win_height - tile_height * 8) / 2
    };
    Group board;
    checkerboard(board, tl, tile_width, tile_height, Color::red, Color::black, Color::dark_magenta, Color::white);
    board.attach_to(win);

    while (true) {
        for (int i = 0; i < 8; ++i) {
            win.wait_for_button();
            int idx = board.size() - 1 - i % 4;
            board.move(idx, 0, (i > 3 ? -1 : 1) * tile_height);
        }
    }
}
