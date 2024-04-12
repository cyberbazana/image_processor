#include "image.h"
#include "bmp.h"

std::vector<std::vector<RGB>>* Image::GetPixels() {
    return &image_;
}
Image::Image() {
    width_ = 1;
    height_ = 1;
}
FileHeader Image::GetFileHeader() const {
    FileHeader file_header;
    file_header.bfType[0] = 'B';
    file_header.bfType[1] = 'M';
    unsigned char buffer[4];
    Set32bit(54 + (width_ + (4 - ((width_ * 3) % 4)) % 4) * 3 * height_, buffer);  // NOLINT
    CopyBuffer32bit(file_header.bfSize, buffer);
    file_header.bfReserved1[0] = 0;
    file_header.bfReserved1[1] = 0;
    file_header.bfReserved2[0] = 0;
    file_header.bfReserved2[1] = 0;
    Set32bit(54, buffer);  // NOLINT
    CopyBuffer32bit(file_header.bfOffBits, buffer);
    return file_header;
}
BitMapFileHeader Image::GetBitMapFileHeader() const {
    BitMapFileHeader bit_map_file_header;
    unsigned char buffer[4];
    Set32bit(40, buffer);  // NOLINT
    CopyBuffer32bit(bit_map_file_header.biSize, buffer);
    Set32bit(width_, buffer);  // NOLINT
    CopyBuffer32bit(bit_map_file_header.biWidth, buffer);
    Set32bit(height_, buffer);  // NOLINT
    CopyBuffer32bit(bit_map_file_header.biHeight, buffer);
    unsigned char buffer_small[2];
    Set16bit(1, buffer_small);
    CopyBuffer16bit(bit_map_file_header.biPlanes, buffer_small);
    Set16bit(24, buffer_small);  // NOLINT
    CopyBuffer16bit(bit_map_file_header.biBitCount, buffer_small);
    Set32bit(biCompression_, buffer);
    CopyBuffer32bit(bit_map_file_header.biCompression, buffer);
    Set32bit(biSizeImage_, buffer);
    CopyBuffer32bit(bit_map_file_header.biSizeImage, buffer);
    Set32bit(biXPerMeter_, buffer);
    CopyBuffer32bit(bit_map_file_header.biXPerMeter, buffer);
    Set32bit(biYPerMeter_, buffer);
    CopyBuffer32bit(bit_map_file_header.biYPerMeter, buffer);
    Set32bit(biClrUsed_, buffer);
    CopyBuffer32bit(bit_map_file_header.biClrUsed, buffer);
    Set32bit(biClrImportant_, buffer);
    CopyBuffer32bit(bit_map_file_header.biClrImportant, buffer);
    return bit_map_file_header;
}
Image::Image(int32_t width, int32_t height, std::vector<std::vector<RGB>> data, int32_t bi_compression,
             int32_t bi_size_image, int32_t bi_x_per_meter, int32_t bi_y_per_meter, int32_t bi_clr_used,
             int32_t bi_clr_important) {
    image_ = data;
    width_ = width;
    height_ = height;
    biCompression_ = bi_compression;
    biSizeImage_ = bi_size_image;
    biXPerMeter_ = bi_x_per_meter;
    biYPerMeter_ = bi_y_per_meter;
    biClrUsed_ = bi_clr_used;
    biClrImportant_ = bi_clr_important;
}
