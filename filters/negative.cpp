#include "negative.h"

void Negative::Apply(Image &image) const {
    auto pixels = image.GetPixels();
    for (auto &i : *pixels) {
        for (auto &j : i) {
            j.red = 1 - j.red;
            j.green = 1 - j.green;
            j.blue = 1 - j.blue;
        }
    }
}

Negative::Negative() = default;
