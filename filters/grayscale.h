#pragma once

#include "base.h"

class GrayScale : public BaseFilter {
public:
    GrayScale();

    void Apply(Image &image) const override;
};