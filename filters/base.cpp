#include "base.h"

BaseFilter::~BaseFilter() = default;
void BaseFilter::ApplyMatrix(Image& image, std::vector<double> matrix) const {
    auto pixels = image.GetPixels();
    std::vector<std::vector<RGB>> mask = *pixels;
    for (int i = 0; i < image.height_; ++i) {
        for (int j = 0; j < image.width_; ++j) {
            size_t left_border = std::max(0, j - 1);
            size_t right_border = std::min(image.width_ - 1, j + 1);
            size_t top_border = std::max(0, i - 1);
            size_t bottom_border = std::min(image.height_ - 1, i + 1);
            pixels->at(i)[j].red = std::min(
                1.0,
                std::max(0.0,
                         matrix[0] * mask[top_border][left_border].red + matrix[1] * mask[top_border][j].red +
                             matrix[2] * mask[top_border][right_border].red + matrix[3] * mask[i][left_border].red +
                             matrix[4] * mask[i][j].red + matrix[5] * mask[i][right_border].red +  // NOLINT
                             matrix[6] * mask[bottom_border][left_border].red +                    // NOLINT
                             matrix[7] * mask[bottom_border][j].red +                              // NOLINT
                             matrix[8] * mask[bottom_border][right_border].red                     // NOLINT
                         ));
            pixels->at(i)[j].green = std::min(
                1.0,
                std::max(0.0,
                         matrix[0] * mask[top_border][left_border].green + matrix[1] * mask[top_border][j].green +
                             matrix[2] * mask[top_border][right_border].green + matrix[3] * mask[i][left_border].green +
                             matrix[4] * mask[i][j].green + matrix[5] * mask[i][right_border].green +  // NOLINT
                             matrix[6] * mask[bottom_border][left_border].green +                      // NOLINT
                             matrix[7] * mask[bottom_border][j].green +                                // NOLINT
                             matrix[8] * mask[bottom_border][right_border].green                       // NOLINT
                         ));
            pixels->at(i)[j].blue = std::min(
                1.0,
                std::max(0.0,
                         matrix[0] * mask[top_border][left_border].blue + matrix[1] * mask[top_border][j].blue +
                             matrix[2] * mask[top_border][right_border].blue + matrix[3] * mask[i][left_border].blue +
                             matrix[4] * mask[i][j].blue + matrix[5] * mask[i][right_border].blue +  // NOLINT
                             matrix[6] * mask[bottom_border][left_border].blue +                     // NOLINT
                             matrix[7] * mask[bottom_border][j].blue +                               // NOLINT
                             matrix[8] * mask[bottom_border][right_border].blue                      // NOLINT
                         ));
        }
    }
}
