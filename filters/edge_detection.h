#pragma once

#include "base.h"

class EdgeDetection : public BaseFilter {
public:
    explicit EdgeDetection(double threshold);

    void Apply(Image& image) const override;

private:
    double threshold_;
};