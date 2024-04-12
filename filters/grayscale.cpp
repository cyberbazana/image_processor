#include "grayscale.h"

GrayScale::GrayScale() = default;

void GrayScale::Apply(Image &image) const {
    auto pixels = image.GetPixels();
    for (auto &i : *pixels) {
        for (auto &j : i) {
            auto color = 0.299 * j.red + 0.587 * j.green + 0.114 * j.blue;  // NOLINT
            j.red = color;
            j.green = color;
            j.blue = color;
        }
    }
}
