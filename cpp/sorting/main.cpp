#include "algorithm.hpp"
#include <iostream>

template<typename T>
void print(const std::vector<T>& vec) {
    for (const auto& elem : vec) {
        std::cout << elem << " ";
    }
    std::cout << std::endl;
}

int main() {
    auto data = SortingAlgorithm<int>::makeData(20);
    print(data);
    auto sorted = SortingAlgorithm<int>::mergeSort(data);
    print(sorted);
    return 0;
}