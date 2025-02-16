#include "PPP/Simple_window.h"
#include "PPP/Graph.h"

// Get a heap-allocated array of contiguous elements from the operating system
Rectangle* get_uninitialized(int number) {
    return static_cast<Rectangle*>(operator new(number * sizeof(Rectangle)));
}

// Check if current tile should be colored in a checkerboard pattern
bool is_colored(int i, int columns) {
    return (columns % 2 || i / columns % 2 == 0) ? i % 2 : i % 2 == 0;
}

// Construct uninitialized array of Rectangle-s
void construct_board(Rectangle*& board, int board_columns, int board_rows, int rect_width, int rect_height) {
    int x = 0;
    int y = 0;
    for (int i = 0; i < board_columns * board_rows; ++i, x += rect_width) {
        // Check for entering new row
        if (i && i % board_columns == 0) {
            x = 0;
            y += rect_height;
        }
        // Placement new: construct element in uninitialized memory
        new (board + i) Rectangle {Point{x, y}, rect_width, rect_height};
        if (is_colored(i, board_columns))
            board[i].set_fill_color(Color::red);
    }
}

// Paint each element in the heap-allocated array
void attach_each(Window& win, Rectangle* rect, int size) {
    for (Rectangle* p = rect; p != rect + size; ++p)
        win.attach(*p);
}

// Call the destructor on each element in reverse order
void destroy_board(Rectangle* arr, int size) {
    for (Rectangle* p = arr + size; p > arr; )
        (--p)->~Rectangle();
}

// Give the previously allocated memory back to the operating system
void deallocate(Rectangle*& p) {
    operator delete(p);
}

int main(int /*argc*/, char * /*argv*/[])
{
    // Make Graph_lib's contents available implicitly without using its scope
    using namespace Graph_lib;

    // Initialize display engine
    Application app;

    // Window top-left point
    constexpr int win_x = 600;
    constexpr int win_y = 400;

    // Window size
    constexpr int win_width = 800;
    constexpr int win_height = 600;

    // Create window
    const std::string label = "Tic-Tac-Toe Board";
    Simple_window win{Point{win_x, win_y}, win_width, win_height, label};

    // Change these to generate boards of different sizes
    constexpr int board_columns = 3;
    constexpr int board_rows = 3;

    // Amount of tiles on board
    constexpr int board_size = board_columns * board_rows;

    // Rectangle sizes
    constexpr int rect_width = win_width / board_columns;
    constexpr int rect_height = win_height / board_rows;

    // Since Rectangle doesn't have copy and move constructors,
    // we can't pass objects of type Rectangle to functions,
    // can't attach local-to-function objects to Window objects,
    // or put them into vectors.
    // I wanted to have a container of Rectangles, into which I could
    // insert elements based on the algorithm inside construct_board(...),
    // instead of writing 9 different Rectangle declarations in main().
    // I solved this problem using operator new, which allocates uninitialized
    // memory that we need to manually construct using placement new somewhere else
    // (which is what we want!).
    // We need to be sure to return all heap-allocated memory to the operating system,
    // which is done by first iterating over each element from last to first to
    // call their destructors manually, then calling operator delete
    // on the originally returned pointer by operator new.
    //
    // Dealing with pointers is error-prone!
    Rectangle* board = get_uninitialized(board_size);
    construct_board(board, board_columns, board_rows, rect_width, rect_height);

    // Paint the elements of the board array
    attach_each(win, board, board_size);

    // Don't exit immediately upon start
    win.wait_for_button();

    // Close when button is pressed, don't rely on out-of-scope closing,
    // as cleaning up the board might take a while
    win.close();

    // Clean up board contents
    destroy_board(board, board_size);
    deallocate(board);

    // Set to invalid state just in case
    board = nullptr;
}
