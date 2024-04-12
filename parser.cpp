#include <stdexcept>
#include "parser.h"
#include "exceptions/filter_exceptions.h"

ParserResults Parse(int argc, char** argv) {
    if (argc <= 1) {
        throw FilterNothingToDoException();
    }
    if (argc == 2) {
        throw FilterParsingException();
    }
    std::vector<FilterDescription> filter_descriptions;
    int index = 3;
    try {
        while (index < argc) {
            auto x = std::string{argv[index]};
            if (x == "-crop") {
                filter_descriptions.emplace_back(
                    FilterDescription{x, std::vector<std::string>{argv[index + 1], argv[index + 2]}});
                index += 3;
                continue;
            }
            if (x == "-gs") {
                filter_descriptions.emplace_back(FilterDescription{x, std::vector<std::string>{}});
                ++index;
                continue;
            }
            if (x == "-neg") {
                filter_descriptions.emplace_back(FilterDescription{x, std::vector<std::string>{}});
                ++index;
                continue;
            }
            if (x == "-sharp") {
                filter_descriptions.emplace_back(FilterDescription{x, std::vector<std::string>{}});
                ++index;
                continue;
            }
            if (x == "-edge") {
                filter_descriptions.emplace_back(FilterDescription{"-gs", std::vector<std::string>{}});
                filter_descriptions.emplace_back(FilterDescription{x, std::vector<std::string>{argv[index + 1]}});
                index += 2;
                continue;
            }
            if (x == "-blur") {
                filter_descriptions.emplace_back(FilterDescription{x, std::vector<std::string>{argv[index + 1]}});
                index += 2;
                continue;
            }
            if (x == "-crystal") {
                filter_descriptions.emplace_back(FilterDescription{x, std::vector<std::string>{argv[index + 1]}});
                index += 2;
                continue;
            }
            ++index;
            throw FilterParsingException();
        }
    } catch (const std::out_of_range& err) {
        throw FilterParsingException();
    }
    return {argv[1], argv[2], filter_descriptions};
}