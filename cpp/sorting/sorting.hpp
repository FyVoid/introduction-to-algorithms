#pragma once

#include <vector>
#include <concepts>
#include "helper.hpp"
#include <iostream>
#include <algorithm>

template<std::totally_ordered T>
class SortingAlgorithm {
public:
    static std::vector<T> shuffle(const std::vector<T>& data) {
        auto ret = data;
        for (size_t i = 0; i < ret.size(); i++) {
            auto j = get_rand<size_t>(i, ret.size() - 1);
            std::swap(ret[i], ret[j]);
        }
        return ret;
    }
    static std::vector<T> make_data(size_t n) {
        std::vector<T> ret(n);
        for (size_t i = 0; i < n; i++) {
            ret[i] = get_rand<T>(0, static_cast<T>(n));
        }
        return ret;
    }
    static std::vector<T> insertion_sort(const std::vector<T>& data) {
        auto ret = data;
        for (size_t i = 1; i < ret.size(); i++) {
            auto key = ret[i];
            int j = i - 1;
            while (j >= 0 && ret[j] > key) {
                ret[j + 1] = ret[j];
                j--;
            }
            ret[j + 1] = key;
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
    static std::vector<T> merge_sort(const std::vector<T>& data) {
        auto ret = data;
        merge(ret, 0, ret.size());
        return ret;
    }
    static std::vector<T> bubble_sort(const std::vector<T>& data) {
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
    static std::vector<T> heap_sort(const std::vector<T>& data) {
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
private:
    static size_t partition(std::vector<T>& data, size_t begin, size_t end) {
        auto pivot = data[begin];
        auto left = begin + 1;
        auto right = end - 1;

        while (true) {
            while (left < right && data[left] < pivot) {
                left++;
            }
            while (right > left && data[right] > pivot) {
                right--;
            }
            if (left >= right) {
                break;
            }
            std::swap(data[left], data[right]);
            left++;
            right--;
        }

        std::swap(data[begin], data[right]);

        return right;
    }
    static size_t random_partition(std::vector<T>& data, size_t begin, size_t end) {
        auto pivot_index = get_rand<size_t>(begin, end - 1);
        std::swap(data[begin], data[pivot_index]);
        return partition(data, begin, end);
    }
    static void qsort(std::vector<T>& data, size_t begin, size_t end) {
        if (begin + 1 < end) {
            auto mid = random_partition(data, begin, end);
            qsort(data, begin, mid);
            qsort(data, mid + 1, end);
        }
    }
public:
    static std::vector<T> quick_sort(const std::vector<T>& data) {
        auto ret = data;
        qsort(ret, 0, data.size());
        return ret;
    }
    static std::vector<T> counting_sort(const std::vector<T>& data, T maxValue) {
        std::vector<size_t> count(maxValue + 1, 0);
        for (const auto& elem : data) {
            count[elem]++;
        }
        std::vector<T> ret;
        for (size_t i = 0; i < count.size(); i++) {
            for (size_t j = 0; j < count[i]; j++) {
                ret.push_back(static_cast<T>(i));
            }
        }
        return ret;
    }
    static std::vector<int> radix_sort(const std::vector<int>& data)
        requires std::is_same_v<T, int> {
        if (data.empty()) return data;
        
        std::vector<int> ret = data;
        std::vector<int> buffer(data.size());
        
        for (int& num : ret) {
            num ^= (1 << 31);
        }
        
        constexpr int BITS = sizeof(int) * 8;
        
        for (int i = 0; i < BITS; i++) {
            size_t count = 0;
            for (const auto& num : ret) {
                count += ((num >> i) & 1);
            }
            size_t zero_index = 0;
            size_t one_index = ret.size() - count;
            for (const auto& num : ret) {
                if ((num >> i) & 1) {
                    buffer[one_index++] = num;
                } else {
                    buffer[zero_index++] = num;
                }
            }
            std::swap(ret, buffer);
        }
        for (int& num : ret) {
            num ^= (1 << 31);
        }
        
        return ret;
    }
    static std::vector<T> bucket_sort(const std::vector<T>& data, size_t bucketCount) {
        if (data.empty()) return data;
        T minValue = *std::min_element(data.begin(), data.end());
        T maxValue = *std::max_element(data.begin(), data.end());
        T range = maxValue - minValue + 1;
        std::vector<std::vector<T>> buckets(bucketCount);
        for (const auto& elem : data) {
            size_t index = (elem - minValue) * bucketCount / range;
            if (index == bucketCount) index--;
            buckets[index].push_back(elem);
        }
        std::vector<T> ret;
        for (auto& bucket : buckets) {
            std::sort(bucket.begin(), bucket.end());
            ret.insert(ret.end(), bucket.begin(), bucket.end());
        }
        return ret;
    }
};

template class SortingAlgorithm<int>;