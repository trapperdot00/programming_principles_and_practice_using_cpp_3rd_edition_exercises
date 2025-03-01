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
    constexpr int win_width = 800;
    constexpr int win_height = 1000;
    const std::string label = "Images inside grid fields";
    Simple_window win{Point{win_x, win_y}, win_width, win_height, label};

    // Grid
    constexpr int grid_cols = 8;
    constexpr int grid_rows = 8;
    constexpr int grid_width = 800;
    constexpr int grid_height = 800;
    constexpr int grid_col_width = grid_width / grid_cols;
    constexpr int grid_row_height = grid_height / grid_rows;
    Lines grid;
    for (int x = grid_col_width; x <= grid_width; x += grid_col_width) {
        grid.add(Point{x, 0}, Point{x, grid_height});
        std::cout << x << ';' << 0 << '\t' << x << ';' << grid_height << '\n';
    }
    for (int y = grid_row_height; y <= grid_height; y += grid_row_height) {
        grid.add(Point{0, y}, Point{grid_width, y});
        std::cout << 0 << ';' << y << '\t' << grid_width << ';' << y << '\n';
    }
    win.attach(grid);

    // Diagonal red fields
    Vector_ref<Rectangle> rects;
    for (Point tl{0, 0};
         tl.x <= grid_width - grid_col_width && tl.y <= grid_height - grid_row_height;
         tl.x += grid_col_width, tl.y += grid_row_height) {
        rects.push_back(std::make_unique<Rectangle>(tl, grid_col_width, grid_row_height));
    }
    for (Rectangle* rect : rects) {
        rect->set_fill_color(Color::red);
        win.attach(*rect);
    }

    // Top-left fields to put images in
    constexpr std::array<std::pair<int, int>, 3> field_index = {{
        {3, 1}, {5, 3}, {2, 4}
    }};
    const std::string vro_path = "../../toletole.png";
    Vector_ref<Image> vros;
    for (size_t i = 0; i < field_index.size(); ++i) {
        const std::pair<int, int>& indices = field_index[i];
        vros.push_back(std::make_unique<Image>(
            Point{indices.first * grid_col_width, indices.second * grid_row_height}, vro_path
        ));
    }
    for (Image* vro : vros)
        win.attach(*vro);

    // Moving image
    const std::string bingus_path = "../../bingus.png";
    int bingus_x = 0;
    int bingus_y = 0;
    Image bingus{Point{bingus_x, bingus_y}, bingus_path};
    win.attach(bingus);

    // To calculate delta coordinates for moving
    int bingus_prev_x = 0;
    int bingus_prev_y = 0;

    // Move on each press of a button
    while (true) {
        win.wait_for_button();
        // Move left-to-right, up to down
        if (bingus_x < (grid_cols - 1) * grid_col_width) {
            bingus_x += grid_col_width;
        } else {
            bingus_x = 0;
            if (bingus_y < (grid_rows - 1) * grid_row_height)
                bingus_y += grid_row_height;
            else
                bingus_y = 0;
        }
        int dx = bingus_x - bingus_prev_x;
        int dy = bingus_y - bingus_prev_y;
        bingus.move(dx, dy);
        bingus_prev_x = bingus_x;
        bingus_prev_y = bingus_y;
    }
}
