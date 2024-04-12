#include "sharpening.h"

Sharpening::Sharpening() = default;

void Sharpening::Apply(Image &image) const {
    std::vector<double> matrix{0.0, -1.0, 0.0, -1.0, 5.0, -1.0, 0.0, -1.0, 0.0};  // NOLINT
    ApplyMatrix(image, matrix);
}
