#include "PPP/Simple_window.h"
#include "PPP/Graph.h"

#include <cstring>

// Holds an image's size
struct Image_size {
    int width;
    int height;
};

// Check if host is big endian
bool big_endian() {
    union {
        uint32_t i;
        char c[4];
    } val{0x01020304};
    return val.c[0] == 1;
}

// Painful conversion from big endian to host endianness
uint32_t read_big_endian_fourbytes(std::istream& is) {
    uint32_t value = 0;
    if (big_endian()) {
        is.read(reinterpret_cast<char*>(&value), 4);
    } else {
        char c = 0;
        // Construct integer in reverse byte order
        for (size_t byte_count = 0; byte_count < 4 && is.get(c); ++byte_count) {
            value |= uint32_t(static_cast<unsigned char>(c)) << (3 - byte_count) * 8;
        }
    }
    if (!is)
        throw std::runtime_error{"reading failed"};
    return value;
}

// Get the size of a PNG picture
Image_size get_size(const std::string& filename) {
    static constexpr char png_header[9] = "\x89PNG\r\n\x1A\n";
    std::ifstream is{filename, std::ios_base::binary};
    if (!is)
        throw std::runtime_error{"can't open " + filename + " for reading"};
    // Read PNG header
    char header[9] = {};
    is.read(header, 8);
    if (std::strcmp(header, png_header) != 0)
        throw std::runtime_error{"bad png header"};

    // Go to image size data start location in the file
    is.seekg(16, std::ios_base::beg);

    // Read size
    int width = read_big_endian_fourbytes(is);
    int height = read_big_endian_fourbytes(is);

    return Image_size{width, height};
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
    constexpr int win_width = 400;
    constexpr int win_height = 400;

    // Create window
    const std::string label = "Cat image";
    Simple_window win{Point{win_x, win_y}, win_width, win_height, label};

    // Create an image of my cat, centered horizontally and vertically
    Image_size cat_size = get_size("../../cat.png");
    int cat_x = (win_width - cat_size.width) / 2;
    int cat_y = (win_height - cat_size.height) / 2;
    Image cat{Point{cat_x, cat_y}, "../../cat.png"};

    // Create label under the image
    std::string text = "Mini";
    constexpr int font_size = 32;
    Text cat_label{Point{cat_x, cat_y + cat_size.height}, text};
    cat_label.set_font(Font::times);
    cat_label.set_font_size(font_size);

    // Create box for label
    Rectangle box{Point{cat_x, cat_y + cat_size.height}, cat_size.width - 1, font_size};

    win.attach(cat);
    win.attach(cat_label);
    win.attach(box);

    win.wait_for_button();
}
