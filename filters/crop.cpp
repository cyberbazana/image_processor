#include <iostream>
#include "crop.h"

Crop::Crop(int width, int height) : width_(width), height_(height) {
}

void Crop::Apply(Image &image) const {
    auto pixels = image.GetPixels();
    pixels->resize(std::min(height_, image.height_));
    for (auto &i : *pixels) {
        i.resize(std::min(width_, image.width_));
    }
    image.width_ = std::min(width_, image.width_);
    image.height_ = std::min(height_, image.height_);
}
