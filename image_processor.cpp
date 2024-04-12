#include <iostream>
#include <vector>
#include "bmp.h"
#include "image.h"
#include "processor.h"
#include "parser.h"
#include "exceptions/file_read_exceptions.h"
#include "exceptions/filter_exceptions.h"
#include <memory>

int main(int argc, char** argv) {
    ParserResults filters;
    try {
        filters = Parse(argc, argv);
    } catch (FilterNothingToDoException& e) {
        std::cout << FilterNothingToDoException::Message();
        return 0;
    } catch (FilterParsingException& e) {
        std::cout << FilterParsingException::Message();
        return 0;
    }
    Image img;
    try {
        img = GetImage(filters.path_file_in);
    } catch (InDirectoryException& e) {
        std::cout << InDirectoryException::Message();
        return 0;
    } catch (ImageFormatException& e) {
        std::cout << ImageFormatException::Message();
        return 0;
    }
    std::vector<std::unique_ptr<BaseFilter>> tmp;
    try {
        tmp = CreateFilters(filters.filter_descriptions);
    } catch (FilterArgumentsException& e) {
        std::cout << FilterArgumentsException::Message();
        return 0;
    }
    ApplyFilters(tmp, img);
    try {
        SaveImage(img, filters.path_file_out);
    } catch (OutDirectoryException& e) {
        std::cout << OutDirectoryException::Message();
        return 0;
    }
    return 0;
}