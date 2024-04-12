#include "edge_detection.h"

EdgeDetection::EdgeDetection(double threshold) {
    threshold_ = threshold;
}

void EdgeDetection::Apply(Image &image) const {
    std::vector<double> matrix{0.0, -1.0, 0.0, -1.0, 4.0, -1.0, 0.0, -1.0, 0.0};  // NOLINT
    ApplyMatrix(image, matrix);
    auto pixels = image.GetPixels();
    for (auto &pixel : *pixels) {
        for (auto &j : pixel) {
            if (j.red > threshold_ && j.green > threshold_ && j.blue > threshold_) {
                j.red = 1.0;
                j.green = 1.0;
                j.blue = 1.0;
            } else {
                j.red = 0.0;
                j.green = 0.0;
                j.blue = 0.0;
            }
        }
    }
}
