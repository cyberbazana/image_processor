#pragma once

#include <exception>
#include <string>

class OutDirectoryException : public std::exception {
public:
    static std::string Message() {
        return "Error occurred while saving the image";
    }
};

class InDirectoryException : public std::exception {
public:
    static std::string Message() {
        return "Error occurred while opening the image";
    }
};

class ImageFormatException : public std::exception {
public:
    static std::string Message() {
        return "Sorry, this type not supported";
    }
};