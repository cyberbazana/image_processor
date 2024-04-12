#pragma once

#include <string>
#include <vector>

struct FilterDescription {
    std::string filter_name;
    std::vector<std::string> filter_arguments;
};

struct ParserResults {
    const char *path_file_in;
    const char *path_file_out;
    std::vector<FilterDescription> filter_descriptions;
};

ParserResults Parse(int argc, char **argv);