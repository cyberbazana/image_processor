#include <fstream>
#include <concepts>
#include "exceptions/file_read_exceptions.h"

class BinaryReader {
public:
    explicit BinaryReader(const std::string& path_file_in) {
        in_ = std::ifstream(path_file_in, std::ios::binary);
        if (!in_) {
            throw InDirectoryException();
        }
    }

    template <typename T>
    BinaryReader& operator>>(T& value) {
        in_.read(reinterpret_cast<char*>(&value), sizeof(T));
        return *this;
    }

    void SeekFromStart(int value) {
        in_.seekg(value);
    }

    void SeekFromCur(int value) {
        in_.seekg(value, std::ios::cur);
    }

private:
    std::ifstream in_;
};

class BinaryWriter {
public:
    explicit BinaryWriter(const std::string& path_file_out) {
        out_ = std::ofstream(path_file_out, std::ios::binary);
        if (!out_ || !CheckOutDirectory(path_file_out)) {
            throw OutDirectoryException();
        }
    }
    template <typename T>
    BinaryWriter& operator<<(T& value) {
        out_.write(reinterpret_cast<char*>(&value), sizeof(T));
        return *this;
    }
    static bool CheckOutDirectory(const std::string& file_path) {
        auto pos = file_path.rfind('.');
        if (pos != SIZE_MAX) {
            return file_path.substr(pos, 4) == ".bmp";
        }
        return false;
    }

private:
    std::ofstream out_;
};
