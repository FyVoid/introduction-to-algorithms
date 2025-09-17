#include "algorithm.hpp"
#include <iostream>
#include <algorithm>
#include <chrono>
#include <functional>

template<typename T>
void print(const std::vector<T>& vec) {
    for (const auto& elem : vec) {
        std::cout << elem << " ";
    }
    std::cout << std::endl;
}

void time_it(std::function<void()> func) {
    auto start = std::chrono::high_resolution_clock::now();
    func();
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> duration = end - start;
    std::cout << "Time taken: " << duration.count() << " ms" << std::endl;
}

int main() {
    auto data = SortingAlgorithm<int>::makeData(100);
    print(data);
    auto standard = data;
    std::sort(standard.begin(), standard.end());
    print(standard);
    time_it([data]() {
        auto sorted = SortingAlgorithm<int>::radixSort(data);
        print(sorted);
    });
    return 0;
}