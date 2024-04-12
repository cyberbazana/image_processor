#include "gauss.h"
#include "cmath"

Gauss::Gauss(double sigma) {
    sigma_ = sigma;
}

void Gauss::Apply(Image &image) const {
    auto pixels = image.GetPixels();
    std::vector<std::vector<RGB>> mask = *pixels;
    int rs = std::ceil(sigma_ * 2.57);  // NOLINT
    std::vector<double> matrix_coef;
    matrix_coef.reserve(2 * rs + 1);
    for (int i = 0; i < 2 * rs + 1; ++i) {
        matrix_coef.push_back(std::exp(-((i - rs) * (i - rs)) / (2 * sigma_ * sigma_)));
    }
    double sumix = 0;
    for (int i = 0; i < 2 * rs + 1; ++i) {
        sumix += matrix_coef[i];
    }
    for (int i = 0; i < image.height_; ++i) {
        for (int j = 0; j < image.width_; ++j) {
            double red = 0.0;
            double green = 0.0;
            double blue = 0.0;
            std::vector<int> indexes;
            indexes.reserve(2 * rs + 1);
            for (int k = 0; k < 2 * rs + 1; ++k) {
                indexes.push_back(std::min(std::max(j - rs + k, 0), image.width_ - 1));
            }
            int counter = 0;
            for (int k : indexes) {
                red += mask[i][k].red * matrix_coef[counter];
                green += mask[i][k].green * matrix_coef[counter];
                blue += mask[i][k].blue * matrix_coef[counter];
                ++counter;
            }
            red /= sumix;
            green /= sumix;
            blue /= sumix;
            pixels->at(i)[j] = RGB{red, green, blue};
        }
    }
    mask = *pixels;
    for (int i = 0; i < image.width_; ++i) {
        for (int j = 0; j < image.height_; ++j) {
            double red = 0.0;
            double green = 0.0;
            double blue = 0.0;
            std::vector<int> indexes;
            indexes.reserve(2 * rs + 1);
            for (int k = 0; k < 2 * rs + 1; ++k) {
                indexes.push_back(std::min(std::max(j - rs + k, 0), image.height_ - 1));
            }
            int counter = 0;
            for (int k : indexes) {
                red += mask[k][i].red * matrix_coef[counter];
                green += mask[k][i].green * matrix_coef[counter];
                blue += mask[k][i].blue * matrix_coef[counter];
                ++counter;
            }
            red /= sumix;
            green /= sumix;
            blue /= sumix;
            pixels->at(j)[i].red = red;
            pixels->at(j)[i].green = green;
            pixels->at(j)[i].blue = blue;

            pixels->at(j)[i].red = std::max(std::min(pixels->at(j)[i].red, 1.0), 0.0);
            pixels->at(j)[i].green = std::max(std::min(pixels->at(j)[i].green, 1.0), 0.0);
            pixels->at(j)[i].blue = std::max(std::min(pixels->at(j)[i].blue, 1.0), 0.0);
        }
    }
}
