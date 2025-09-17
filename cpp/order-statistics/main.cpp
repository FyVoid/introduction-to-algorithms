#include "helper.hpp"
#include "select.hpp"

#include <algorithm>
#include <iostream>

void check_selection(const std::vector<int>& sorted, size_t k, int value) {
    if (value != sorted[k]) {
        throw std::runtime_error("Selection algorithm failed");
    }
    std::cout << "Check complete" << std::endl;
}

int main() {
    auto data = SelectionAlgorithm<int>::shuffle(SelectionAlgorithm<int>::make_data(10000));
    auto k = get_rand<size_t>(0, data.size() - 1);
    auto sorted = data;
    std::sort(sorted.begin(), sorted.end());
    
    std::cout << "k: " << k << std::endl;

    time_it([data, sorted, k]() {
        auto value = SelectionAlgorithm<int>::linear_select(data, k);
        check_selection(sorted, k, value);
    }, "Linear(Sort) Selection Algorithm");

    time_it([data, sorted, k]() {
        auto value = SelectionAlgorithm<int>::random_select(data, k);
        check_selection(sorted, k, value);
    }, "Randomized Selection Algorithm");

    time_it([data, sorted, k]() {
        auto value = SelectionAlgorithm<int>::median_of_medians_select(data, k);
        check_selection(sorted, k, value);
    }, "Median of Medians Selection Algorithm");
}