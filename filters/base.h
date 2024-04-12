#pragma once

#include "../image.h"

class BaseFilter {
public:
    virtual ~BaseFilter();
    virtual void Apply(Image& image) const = 0;

protected:
    void ApplyMatrix(Image& image, std::vector<double> matrix) const;
};
