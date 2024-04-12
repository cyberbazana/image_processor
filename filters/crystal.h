#pragma once

#include "base.h"

class Crystal : public BaseFilter {
public:
    explicit Crystal(int cells);

    void Apply(Image& image) const override;

private:
    int cells_;
};
