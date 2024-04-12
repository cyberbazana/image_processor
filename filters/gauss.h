#pragma once

#include "base.h"

class Gauss : public BaseFilter {
public:
    explicit Gauss(double sigma);

    void Apply(Image& image) const override;

private:
    double sigma_;
};
