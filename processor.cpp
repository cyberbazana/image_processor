#include "processor.h"

std::unique_ptr<BaseFilter> CreateFilter(const FilterDescription& filter_description) {
    auto producer_it = FILTER_PRODUCERS.find(filter_description.filter_name);
    return producer_it->second(filter_description.filter_arguments);
}
std::vector<std::unique_ptr<BaseFilter>> CreateFilters(const std::vector<FilterDescription>& filter_description) {
    std::vector<std::unique_ptr<BaseFilter>> res;
    res.reserve(filter_description.size());
    for (auto& i : filter_description) {
        res.emplace_back(CreateFilter(i));
    }
    return res;
}

void ApplyFilters(const std::vector<std::unique_ptr<BaseFilter>>& filters, Image& image) {
    for (auto& i : filters) {
        i->Apply(image);
    }
}
