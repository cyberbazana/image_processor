#include "crystal.h"
#include "cmath"

Crystal::Crystal(int cells) {
    cells_ = cells;
}

void Crystal::Apply(Image& image) const {
    auto pixels = image.GetPixels();
    std::vector<std::vector<RGB>> mask = *pixels;
    std::vector<std::pair<int, int>> nx;
    nx.reserve(cells_);
    for (int i = 0; i < cells_; ++i) {
        nx.emplace_back(rand() % pixels->size(), rand() % pixels->at(0).size());
    }
    std::vector<RGB> color_palette;
    color_palette.reserve(nx.size());
    for (auto& i : nx) {
        color_palette.push_back(pixels->at(i.first)[i.second]);
    }

    for (int i = 0; i < image.height_; ++i) {
        for (int j = 0; j < image.width_; ++j) {
            std::pair<int, int> coord_pixel;
            int dist = std::numeric_limits<int>::max();
            for (auto& k : nx) {
                int new_dist = std::pow((i - k.first), 2) + std::pow((j - k.second), 2);  // NOLINT
                if (new_dist < dist) {
                    dist = new_dist;
                    coord_pixel.first = k.first;
                    coord_pixel.second = k.second;
                }
            }
            pixels->at(i)[j] = pixels->at(coord_pixel.first)[coord_pixel.second];
        }
    }
}
