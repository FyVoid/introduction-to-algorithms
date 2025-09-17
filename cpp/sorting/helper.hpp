#pragma once

#include <iostream>
#include <chrono>

template<typename T>
void print_vector(const std::vector<T>& vec) {
    for (const auto& elem : vec) {
        std::cout << elem << " ";
    }
    std::cout << std::endl;
}

template<typename F>
void time_it(F f, const std::string& task_name = "Not specified") {
    auto start = std::chrono::high_resolution_clock::now();
    f();
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> duration = end - start;
    std::cout << "Time taken for " << task_name << ": " << duration.count() << " ms" << std::endl;
}