#include "helper.hpp"
#include "select.hpp"

#include <algorithm>
#include <iostream>

void check_selection(const std::vector<int>& sorted, size_t k, int value) {
    if (value != sorted[k]) {
        std::cout << "Error: value does not match sorted[k]" << std::endl;
    }
    std::cout << "Check complete" << std::endl;
}

int main() {
    auto data = SelectionAlgorithm<int>::shuffle(SelectionAlgorithm<int>::make_data(10000));
    auto k = data.size() / 2;
    auto sorted = data;
    std::sort(sorted.begin(), sorted.end());

    time_it([data, sorted, k]() {
        auto [index, value] = SelectionAlgorithm<int>::linear_select(data, k);
        check_selection(sorted, k, value);
    }, "Linear(Sort) Selection Algorithm");

    time_it([data, sorted, k]() {
        auto [index, value] = SelectionAlgorithm<int>::random_select(data, k);
        check_selection(sorted, k, value);
    }, "Randomized Selection Algorithm");
}