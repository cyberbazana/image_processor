#pragma once

#include <exception>
#include <string>

class FilterParsingException : public std::exception {
public:
    static std::string Message() {
        return "Error occurred while reading args of filters";
    }
};

class FilterArgumentsException : public std::exception {
public:
    static std::string Message() {
        return "Error in filter parameters";
    }
};

class FilterNothingToDoException : public std::exception {
public:
    static std::string Message() {
        return "Hi! I'm an image filter.";
    }
};