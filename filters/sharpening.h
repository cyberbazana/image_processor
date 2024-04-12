#pragma once

#include "base.h"

class Sharpening : public BaseFilter {
public:
    explicit Sharpening();

    void Apply(Image& image) const override;
};