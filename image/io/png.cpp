#include "png.h"

#include "libpng/png.h"

#include <cstring>
#include <stdio.h>
#include <string>

bool savePng(const std::string& filename, const Image& image) {
    // TODO: RAII File wrapper
    FILE *fp = fopen(filename.c_str(), "wb");
    if (!fp)
        return false;

    // TODO: RAII PNG wrapper
    png_structp png_ptr = png_create_write_struct
            (PNG_LIBPNG_VER_STRING, nullptr,
             nullptr, nullptr);
    if (!png_ptr)
        return false;

    // TODO: RAII PNG info wrapper
    png_infop info_ptr = png_create_info_struct(png_ptr);
    if (!info_ptr) {
        png_destroy_write_struct(&png_ptr,
                                 (png_infopp)NULL);
        return false;
    }

    if(setjmp(png_jmpbuf(png_ptr)))
        return false;

    png_init_io(png_ptr, fp);

    // Output is 8bit depth, RGBA format.
    png_set_IHDR(
            png_ptr,
            info_ptr,
            image.getWidth(), image.getHeight(),
            8,
            PNG_COLOR_TYPE_RGBA,
            PNG_INTERLACE_NONE,
            PNG_COMPRESSION_TYPE_DEFAULT,
            PNG_FILTER_TYPE_DEFAULT
    );
    png_write_info(png_ptr, info_ptr);

    auto pixel_data = image.data();
    if (!pixel_data)
        return false;

    png_bytep *row_pointers = (png_bytep*)malloc(sizeof(png_bytep) * image.getHeight());
    for(size_t y = 0; y < image.getHeight(); y++) {
        row_pointers[y] = const_cast<png_bytep>(pixel_data + y*image.getRowSize());
    };

    // TODO: Allow to define transformation BGRA (GPU) > RGBA ....
    png_write_image(png_ptr, row_pointers);
    png_write_end(png_ptr, NULL);

    free(row_pointers);

    fclose(fp);

    png_destroy_write_struct(&png_ptr, &info_ptr);

    return true;
}