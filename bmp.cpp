#include "bmp.h"
#include "exceptions/file_read_exceptions.h"
#include "algorithm"
#include "string"
#include "io.h"

void CopyBuffer16bit(unsigned char lhs[], const unsigned char rhs[]) {
    lhs[0] = rhs[0];
    lhs[1] = rhs[1];
}
void Set16bit(int data, unsigned char buffer[]) {
    buffer[0] = data;
    buffer[1] = data >> 8;  // NOLINT
}
int32_t Get32bit(const unsigned char buffer[]) {
    return buffer[0] | buffer[1] << 8 | buffer[2] << 16 | buffer[3] << 24;  // NOLINT
}
int16_t Get16bit(const unsigned char buffer[]) {
    return buffer[0] | buffer[1] << 8;  // NOLINT
}
void CopyBuffer32bit(unsigned char lhs[], const unsigned char rhs[]) {
    lhs[0] = rhs[0];
    lhs[1] = rhs[1];
    lhs[2] = rhs[2];
    lhs[3] = rhs[3];
}
void Set32bit(int data, unsigned char buffer[]) {
    buffer[0] = data;
    buffer[1] = data >> 8;   // NOLINT
    buffer[2] = data >> 16;  // NOLINT
    buffer[3] = data >> 24;  // NOLINT
}
bool CheckFile24Bit(FileHeader& file_header, BitMapFileHeader bit_map_file_header) {
    return file_header.bfType[0] == 'B' && file_header.bfType[1] == 'M' && file_header.bfReserved1[0] == 0 &&
           file_header.bfReserved1[1] == 0 && file_header.bfReserved2[0] == 0 && file_header.bfReserved2[1] == 0 &&
           Get32bit(bit_map_file_header.biSize) >= 40 &&  // NOLINT
           Get16bit(bit_map_file_header.biPlanes) == 1 && Get32bit(bit_map_file_header.biWidth) > 0 &&
           Get32bit(bit_map_file_header.biHeight) > 0;
}
Image GetImage(const char* file_path) {
    BinaryReader binary_reader(file_path);
    FileHeader file_header{};
    try {
        binary_reader >> file_header.bfType;
        binary_reader >> file_header.bfSize;
        binary_reader >> file_header.bfReserved1;
        binary_reader >> file_header.bfReserved2;
        binary_reader >> file_header.bfOffBits;
    } catch (...) {
        throw InDirectoryException();
    }
    BitMapFileHeader bit_map_file_header{};
    try {
        binary_reader >> bit_map_file_header.biSize;
        binary_reader >> bit_map_file_header.biWidth;
        binary_reader >> bit_map_file_header.biHeight;
        binary_reader >> bit_map_file_header.biPlanes;
        binary_reader >> bit_map_file_header.biBitCount;
        binary_reader >> bit_map_file_header.biCompression;
        binary_reader >> bit_map_file_header.biSizeImage;
        binary_reader >> bit_map_file_header.biXPerMeter;
        binary_reader >> bit_map_file_header.biYPerMeter;
        binary_reader >> bit_map_file_header.biClrUsed;
        binary_reader >> bit_map_file_header.biClrImportant;
    } catch (...) {
        throw InDirectoryException();
    }
    if (!CheckFile24Bit(file_header, bit_map_file_header)) {
        throw ImageFormatException();
    }
    int line_padding = (4 - ((Get32bit(bit_map_file_header.biWidth) * 3) % 4)) % 4;
    unsigned char buffer[3];
    try {
        binary_reader.SeekFromStart(Get32bit(file_header.bfOffBits));
    } catch (...) {
        throw InDirectoryException();
    }
    std::vector<std::vector<RGB>> img;
    for (int i = 0; i < Get32bit(bit_map_file_header.biHeight); ++i) {
        std::vector<RGB> tmp;
        for (int j = 0; j < Get32bit(bit_map_file_header.biWidth); ++j) {
            binary_reader >> buffer;
            RGB pixel{buffer[2] / 255.0, buffer[1] / 255.0, buffer[0] / 255.0};  // NOLINT
            tmp.push_back(pixel);
        }
        img.push_back(tmp);
        try {
            binary_reader.SeekFromCur(line_padding);
        } catch (...) {
            throw InDirectoryException();
        }
    }
    std::reverse(img.begin(), img.end());
    Image image(Get32bit(bit_map_file_header.biWidth), Get32bit(bit_map_file_header.biHeight), img,
                Get32bit(bit_map_file_header.biCompression), Get32bit(bit_map_file_header.biSizeImage),
                Get32bit(bit_map_file_header.biXPerMeter), Get32bit(bit_map_file_header.biYPerMeter),
                Get32bit(bit_map_file_header.biClrUsed), Get32bit(bit_map_file_header.biClrImportant));
    return image;
}
void SaveImage(Image& image, const char* file_path) {
    BinaryWriter binary_writer(file_path);
    auto file_header = image.GetFileHeader();
    auto bit_map_file_header = image.GetBitMapFileHeader();
    auto pixels = image.GetPixels();

    unsigned char padding_byte = 0;

    binary_writer << file_header.bfType;
    binary_writer << file_header.bfSize;
    binary_writer << file_header.bfReserved1;
    binary_writer << file_header.bfReserved2;
    binary_writer << file_header.bfOffBits;

    binary_writer << bit_map_file_header.biSize;
    binary_writer << bit_map_file_header.biWidth;
    binary_writer << bit_map_file_header.biHeight;
    binary_writer << bit_map_file_header.biPlanes;
    binary_writer << bit_map_file_header.biBitCount;
    binary_writer << bit_map_file_header.biCompression;
    binary_writer << bit_map_file_header.biSizeImage;
    binary_writer << bit_map_file_header.biXPerMeter;
    binary_writer << bit_map_file_header.biYPerMeter;
    binary_writer << bit_map_file_header.biClrUsed;
    binary_writer << bit_map_file_header.biClrImportant;

    int line_padding = (4 - ((Get32bit(bit_map_file_header.biWidth) * 3) % 4)) % 4;
    std::reverse(pixels->begin(), pixels->end());
    for (size_t i = 0; i < pixels->size(); ++i) {
        for (size_t j = 0; j < pixels->at(0).size(); ++j) {
            unsigned char tmp1 = pixels->at(i).at(j).blue * 255;   // NOLINT
            unsigned char tmp2 = pixels->at(i).at(j).green * 255;  // NOLINT
            unsigned char tmp3 = pixels->at(i).at(j).red * 255;    // NOLINT
            binary_writer << tmp1;
            binary_writer << tmp2;
            binary_writer << tmp3;
        }
        for (int k = 0; k < line_padding; ++k) {
            binary_writer << padding_byte;
        }
    }
}
