#include "image.h"

Image::Image(
    unsigned width,
    unsigned height
)
    : width(width)
    , height(height)
    , bytesPerPixel(4)
    , pixelData(width * height * bytesPerPixel) {
}

size_t Image::toIndex(unsigned row, unsigned column) const {
    return (row * width + column) * bytesPerPixel;
}

const unsigned char* Image::data() const {
    return pixelData.data();
}

unsigned Image::getWidth() const {
    return width;
}

unsigned Image::getHeight() const {
    return height;
}

unsigned Image::getBytesPerPixel() const {
    return bytesPerPixel;
}

unsigned Image::getRowSize() const {
    return getWidth() * getBytesPerPixel();
}

void Image::setPixel(unsigned row, unsigned column, unsigned char r, unsigned char g, unsigned char b, unsigned char a) {
    auto index = toIndex(row, column);
    pixelData[index + 0] = r;
    pixelData[index + 1] = g;
    pixelData[index + 2] = b;
    pixelData[index + 3] = a;
}

void Image::setPixel(unsigned row, unsigned column, std::array<unsigned char, 4> pixel) {
    setPixel(row, column, pixel[0], pixel[1], pixel[2], pixel[3]);
}




