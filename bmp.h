#pragma once

#include <iosfwd>
#include "image.h"

template <typename Type>
void Read(std::ifstream &stream, Type &result, int64_t size);

template <typename Type>
void Write(std::ofstream &stream, Type &result, int64_t size);

int32_t Get32bit(const unsigned char buffer[]);

int16_t Get16bit(const unsigned char buffer[]);

void Set32bit(int data, unsigned char buffer[]);

void Set16bit(int data, unsigned char buffer[]);

void CopyBuffer32bit(unsigned char lhs[], const unsigned char rhs[]);

void CopyBuffer16bit(unsigned char lhs[], const unsigned char rhs[]);

void CopyBuffer32bitInv(unsigned char lhs[], const unsigned char rhs[]);

Image GetImage(const char *file_path);

void SaveImage(Image &img, const char *file_path);