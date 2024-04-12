#pragma once

#include <memory>
#include <vector>

struct RGB {
    double red;
    double green;
    double blue;
};

struct FileHeader {
    unsigned char bfType[2];
    unsigned char bfSize[4];
    unsigned char bfReserved1[2];
    unsigned char bfReserved2[2];
    unsigned char bfOffBits[4];
};

struct BitMapFileHeader {
    unsigned char biSize[4];
    unsigned char biWidth[4];
    unsigned char biHeight[4];
    unsigned char biPlanes[2];
    unsigned char biBitCount[2];
    unsigned char biCompression[4];
    unsigned char biSizeImage[4];
    unsigned char biXPerMeter[4];
    unsigned char biYPerMeter[4];
    unsigned char biClrUsed[4];
    unsigned char biClrImportant[4];
};

class Image {
public:
    Image(int32_t width, int32_t height, std::vector<std::vector<RGB>> data, int32_t bi_compression,
          int32_t bi_size_image, int32_t bi_x_per_meter, int32_t bi_y_per_meter, int32_t bi_clr_used,
          int32_t bi_clr_important);
    Image();

    int32_t width_{};
    int32_t height_{};
    int32_t biCompression_{};
    int32_t biSizeImage_{};
    int32_t biXPerMeter_{};
    int32_t biYPerMeter_{};
    int32_t biClrUsed_{};
    int32_t biClrImportant_{};

    std::vector<std::vector<RGB>> *GetPixels();

    FileHeader GetFileHeader() const;

    BitMapFileHeader GetBitMapFileHeader() const;

private:
    std::vector<std::vector<RGB>> image_;
};