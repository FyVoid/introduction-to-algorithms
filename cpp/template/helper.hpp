#pragma once

#include <iostream>
#include <chrono>
#include <random>

template<typename T>
void print_vector(const std::vector<T>& vec) {
    for (const auto& elem : vec) {
        std::cout << elem << " ";
    }
    std::cout << std::endl;
}

template<typename T>
T get_rand(T minValue, T maxValue) {
    static std::random_device rd;
    static std::mt19937 g(rd());
    if constexpr (std::is_integral_v<T>) {
        std::uniform_int_distribution<T> distrib(minValue, maxValue);
        return static_cast<T>(distrib(g));
    } else {
        std::uniform_real_distribution<T> distrib(minValue, maxValue);
        return static_cast<T>(distrib(g));
    }
}

template<typename F>
void time_it(F f, const std::string& task_name = "Not specified") {
    auto start = std::chrono::high_resolution_clock::now();
    f();
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> duration = end - start;
    std::cout << "Time taken for " << task_name << ": " << duration.count() << " ms" << std::endl;
}