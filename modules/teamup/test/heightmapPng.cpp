#include <png.h>
#include <cstdio>
#include <iostream>
#include "world/generator/generator.h"
#include <easylogging++.h>

INITIALIZE_EASYLOGGINGPP

int renderHeightmap(const std::string& filename, const Teamup::World::Generator::Heightmap& heightmap);

int main(int argc, char** argv) {
    START_EASYLOGGINGPP(argc, argv);
    Teamup::World::Generator::GeneratorSettings settings {
        .width = 1000,
        .height = 1000
    };

    Teamup::World::Generator::Heightmap heightmap = Teamup::World::Generator::generateHeightmap(settings);

    return renderHeightmap("/tmp/test.png", heightmap);
}

int renderHeightmap(const std::string& filename, const Teamup::World::Generator::Heightmap& heightmap) {
    FILE *fp = fopen(filename.c_str(), "wb");
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
            heightmap.width(), // width
            heightmap.height(), // height
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


    png_byte* row = new png_byte[3 * heightmap.width()];
    for (int y = 0; y < heightmap.height(); ++y) {
        for (int x = 0; x < heightmap.width(); ++x) {
            short v = heightmap.get(x, y);
            if (v < 0) {
                // Water. Capped at -10,000
                short cappedValue = std::max((short)-10000, v);
                unsigned char value = (10000 + cappedValue) / 40;
                row[(x * 3) + 0] = 0;
                row[(x * 3) + 1] = 0;
                row[(x * 3) + 2] = value;
                VLOG(9) << "(" << x << ", " << y << ") = Water(" << v << ", " << (int)value << ")";
            } else {
                // Land. Capped at +20,000
                short cappedValue = std::min((short)20000, v);
                unsigned char value = 32 + ((cappedValue / 80) * 7/8);
                row[(x * 3) + 0] = 0;
                row[(x * 3) + 1] = value;
                row[(x * 3) + 2] = 0;
                VLOG(9) << "(" << x << ", " << y << ") = Land(" << v << ", " << (int)value << ")";
            }
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
