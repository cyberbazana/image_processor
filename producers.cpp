#include "producers.h"
#include "exceptions/filter_exceptions.h"

std::unique_ptr<BaseFilter> CreateCropFilter(const std::vector<std::string> &filter_arguments) {
    int64_t width = 0;
    int64_t height = 0;
    try {
        width = std::stoi(filter_arguments[0]);
        height = std::stoi(filter_arguments[1]);
    } catch (...) {
        throw FilterArgumentsException();
    }
    if (width <= 0 || height <= 0) {
        throw FilterArgumentsException();
    }
    return std::make_unique<Crop>(width, height);
}

std::unique_ptr<BaseFilter> CreateGrayFilter(const std::vector<std::string> &filter_arguments) {
    return std::make_unique<GrayScale>();
}

std::unique_ptr<BaseFilter> CreateNegativeFilter(const std::vector<std::string> &filter_arguments) {
    return std::make_unique<Negative>();
}

std::unique_ptr<BaseFilter> CreateBlurFilter(const std::vector<std::string> &filter_arguments) {
    double sigma = 0.0;
    try {
        sigma = std::stod(filter_arguments[0]);
    } catch (...) {
        throw FilterArgumentsException();
    }
    if (sigma < 0) {
        throw FilterArgumentsException();
    }
    return std::make_unique<Gauss>(sigma);
}
std::unique_ptr<BaseFilter> CreateCrystalFilter(const std::vector<std::string> &filter_arguments) {
    int64_t cells = 0;
    try {
        cells = std::stoi(filter_arguments[0]);
    } catch (...) {
        throw FilterArgumentsException();
    }
    if (cells < 0) {
        throw FilterArgumentsException();
    }
    return std::make_unique<Crystal>(cells);
}
std::unique_ptr<BaseFilter> CreateSharpeningFilter(const std::vector<std::string> &filter_arguments) {
    return std::make_unique<Sharpening>();
}
std::unique_ptr<BaseFilter> CreateEdgeFilter(const std::vector<std::string> &filter_arguments) {
    double threshold = 0.0;
    try {
        threshold = std::stod(filter_arguments[0]);
    } catch (...) {
        throw FilterArgumentsException();
    }
    return std::make_unique<EdgeDetection>(threshold);
}
