#pragma once

#include <memory>
#include <string>

#include "filters/base.h"
#include "filters/crop.h"
#include "filters/gauss.h"
#include "filters/grayscale.h"
#include "filters/sharpening.h"
#include "filters/crystal.h"
#include "filters/edge_detection.h"
#include "filters/negative.h"
#include "parser.h"

std::unique_ptr<BaseFilter> CreateCropFilter(const std::vector<std::string> &filter_arguments);

std::unique_ptr<BaseFilter> CreateSharpeningFilter(const std::vector<std::string> &filter_arguments);

std::unique_ptr<BaseFilter> CreateGrayFilter(const std::vector<std::string> &filter_arguments);

std::unique_ptr<BaseFilter> CreateBlurFilter(const std::vector<std::string> &filter_arguments);

std::unique_ptr<BaseFilter> CreateCrystalFilter(const std::vector<std::string> &filter_arguments);

std::unique_ptr<BaseFilter> CreateNegativeFilter(const std::vector<std::string> &filter_arguments);

std::unique_ptr<BaseFilter> CreateEdgeFilter(const std::vector<std::string> &filter_arguments);