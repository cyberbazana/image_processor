#pragma once

#include <memory>
#include <string>
#include <unordered_map>
#include <functional>

#include "filters/base.h"
#include "image.h"
#include "producers.h"
#include "parser.h"

const std::unordered_map<std::string, std::function<std::unique_ptr<BaseFilter>(const std::vector<std::string>)>>
    FILTER_PRODUCERS = {{"-crop", CreateCropFilter},        {"-gs", CreateGrayFilter},   {"-neg", CreateNegativeFilter},
                        {"-sharp", CreateSharpeningFilter}, {"-edge", CreateEdgeFilter}, {"-blur", CreateBlurFilter},
                        {"-crystal", CreateCrystalFilter}};

std::unique_ptr<BaseFilter> CreateFilter(const FilterDescription& filter_description);

std::vector<std::unique_ptr<BaseFilter>> CreateFilters(const std::vector<FilterDescription>& filter_description);

void ApplyFilters(const std::vector<std::unique_ptr<BaseFilter>>& filters, Image& image);