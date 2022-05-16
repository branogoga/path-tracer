#pragma once

#include <array>
#include <vector>

class Image {
public:
    Image(unsigned width, unsigned height);

    Image() = delete;
    Image(const Image&) = delete;
    Image& operator=(const Image&) = delete;

    Image(Image&&) = default;
    Image& operator=(Image&&) = default;

    unsigned getWidth() const;
    unsigned getHeight() const;
    unsigned getBytesPerPixel() const;
    unsigned getRowSize() const;
    void setPixel(unsigned row, unsigned column, unsigned char r, unsigned char g, unsigned char b, unsigned char a = 255);
    void setPixel(unsigned row, unsigned column, std::array<unsigned char, 4> pixel);

    size_t toIndex(unsigned row, unsigned column) const;
    const unsigned char* data() const;
private:
    unsigned width;
    unsigned height;
    unsigned bytesPerPixel;
    std::vector<unsigned char> pixelData;
};