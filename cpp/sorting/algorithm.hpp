#pragma once

#include <vector>
#include <concepts>
#include <random>
#include <iostream>

template<std::totally_ordered T>
class SortingAlgorithm {
public:
    static std::vector<T> makeData(size_t n) {
        std::vector<T> ret(n);
        std::random_device rd;
        std::mt19937 g(rd());
        std::uniform_int_distribution<int> distrib(0, n);
        for (size_t i = 0; i < n; i++) {
            if constexpr (std::is_integral_v<T>) {
            ret[i] = distrib(g);
            } else {
            ret[i] = static_cast<T>(distrib(g));
            }
        }
        return ret;
    }
    static std::vector<T> insertionSort(const std::vector<T>& data) {
        auto ret = data;
        for (size_t i = 1; i < ret.size(); i++) {
            size_t j = i;
            while (j > 0 && ret[j - 1] > ret[i]) {
                j--;
            }
            auto tmp = ret[i];
            for (size_t k = j; k < i; k++) {
                ret[k + 1] = ret[k];
            }
            ret[j] = tmp;
        }
        return ret;
    }
private:
    static void merge(std::vector<T>& data, size_t begin, size_t end) {
        if (end - begin <= 1) {
            return;
        }
        size_t mid = (begin + end) / 2;
        merge(data, begin, mid);
        merge(data, mid, end);
        std::vector<T> tmp;
        auto i = begin, j = mid;
        while (i < mid && j < end) {
            if (data[i] <= data[j]) {
                tmp.push_back(data[i]);
                i++;
            } else {
                tmp.push_back(data[j]);
                j++;
            }
        }
        while (i < mid) {
            tmp.push_back(data[i]);
            i++;
        }
        while (j < end) {
            tmp.push_back(data[j]);
            j++;
        }
        for (size_t i = 0; i < tmp.size(); i++) {
            data[begin + i] = tmp[i];
        }
    }
public:
    static std::vector<T> mergeSort(const std::vector<T>& data) {
        auto ret = data;
        merge(ret, 0, ret.size());
        return ret;
    }
    static std::vector<T> bubbleSort(const std::vector<T>& data) {
        auto ret = data;
        for (size_t i = 0; i < ret.size(); i++) {
            for (size_t j = 0; j < ret.size() - 1 - i; j++) {
                if (ret[j] > ret[j + 1]) {
                    std::swap(ret[j], ret[j + 1]);
                }
            }
        }
        return ret;
    }
private:
    static void heapify(std::vector<T>&data, size_t i, size_t n) {
        size_t largest = i;
        size_t left = 2 * i + 1;
        size_t right = 2 * i + 2;

        if (left < n && data[left] > data[largest]) {
            largest = left;
        }
        if (right < n && data[right] > data[largest]) {
            largest = right;
        }
        if (largest != i) {
            std::swap(data[i], data[largest]);
            heapify(data, largest, n);
        }
    }
public:
    static std::vector<T> heapSort(const std::vector<T>& data) {
        auto ret = data;
        for (int i = ret.size() / 2; i >= 0; i--) {
            heapify(ret, i, ret.size());
        }
        for (int i = ret.size() - 1; i > 0; i--) {
            std::swap(ret[0], ret[i]);
            heapify(ret, 0, i);
        }
        return ret;
    }
};

template class SortingAlgorithm<int>;