#include <png.h>
#include <cstdio>
#include <iostream>

static const unsigned int WIDTH = 256;
static const unsigned int HEIGHT = 256;
int main(void) {
    FILE *fp = fopen("/tmp/test.png", "wb");
    if (fp == nullptr) {
        std::cerr << "Error opening output file" << std::endl;
        return 1;
    }

    png_structp pngPtr = png_create_write_struct(PNG_LIBPNG_VER_STRING, 
            NULL, 
            NULL, 
            NULL);
    if (pngPtr == nullptr) {
        std::cerr << "Error creating write struct" << std::endl;
        return 2;
    }

    png_infop infoPtr = png_create_info_struct(pngPtr);
    if (infoPtr == nullptr) {
        std::cerr << "Error creating info struct" << std::endl;
        return 3;
    }

    png_init_io(pngPtr, fp);
    png_set_IHDR(pngPtr, 
            infoPtr, 
            WIDTH, // width
            HEIGHT, // height
            8, 
            PNG_COLOR_TYPE_RGB,
            PNG_INTERLACE_NONE,
            PNG_COMPRESSION_TYPE_BASE,
            PNG_FILTER_TYPE_BASE);

    png_text titleText {
        .compression = PNG_TEXT_COMPRESSION_NONE,
        .key = (png_charp)"Title",
        .text = (png_charp)"Test"
    };
    png_set_text(pngPtr, infoPtr, &titleText, 1);

    png_write_info(pngPtr, infoPtr);


    png_byte* row = new png_byte[3 * WIDTH];
    for (int y = 0; y < HEIGHT; ++y) {
        for (int x = 0; x < WIDTH; ++x) {
            row[(x * 3) + 0] = x;
            row[(x * 3) + 1] = y;
            row[(x * 3) + 2] = 0;
        }
        png_write_row(pngPtr, row);
    }

    delete[] row;

    png_write_end(pngPtr, nullptr);
    fclose(fp);
    png_free_data(pngPtr, infoPtr, PNG_FREE_ALL, -1);
    png_destroy_write_struct(&pngPtr, nullptr);
    return 0;
}
