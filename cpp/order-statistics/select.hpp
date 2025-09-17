#pragma once

#include "helper.hpp"
#include <concepts>
#include <vector>
#include <tuple>
#include <algorithm>
#include <iostream>

template<std::totally_ordered T>
class SelectionAlgorithm {
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
    static T linear_select(const std::vector<T>& data, size_t k) {
        auto cpy = data;
        std::sort(cpy.begin(), cpy.end());
        return cpy[k];
    }
private:
    static size_t partition(std::vector<T>& data, size_t pivot_index, size_t begin, size_t end) {
        auto pivot = data[pivot_index];
        std::swap(data[pivot_index], data[end - 1]);

        size_t store_index = begin;
        for (size_t i = begin; i < end - 1; i++) {
            if (data[i] < pivot) {
                std::swap(data[i], data[store_index]);
                store_index++;
            }
        }
        std::swap(data[store_index], data[end - 1]);
        return store_index;
    }
    static size_t random_partition(std::vector<T>& data, size_t begin, size_t end) {
        auto pivot_index = get_rand<size_t>(begin, end - 1);
        return partition(data, pivot_index, begin, end);
    }
    static T rselect(std::vector<T>& data, size_t k, size_t begin, size_t end) {
        auto partition = random_partition(data, begin, end);
        if (partition == k) {
            return data[partition];
        }
        else if (partition > k) {
            return rselect(data, k, begin, partition);
        } else {
            return rselect(data, k, partition + 1, end);
        }
    }
public:
    // return k-th smallest element and its index in the original array
    static T random_select(const std::vector<T>& data, size_t k) {
        auto cpy = data;
        return rselect(cpy, k, 0, cpy.size());
    }
private:
    static const size_t MOM_GROUP_SIZE = 5;
    static size_t select(std::vector<T>& data, size_t begin, size_t end) {
        if (end - begin <= MOM_GROUP_SIZE) {
            std::sort(data.begin() + begin, data.begin() + end);
            return begin + (end - 1 - begin) / 2;
        }

        int medians = 0;
        for (size_t i = begin; i < end; i += MOM_GROUP_SIZE) {
            size_t group_end = std::min(i + MOM_GROUP_SIZE, end);
            std::sort(data.begin() + i, data.begin() + group_end);
            size_t median_index = i + (group_end - 1 - i) / 2;
            std::swap(data[begin + (i - begin) / MOM_GROUP_SIZE], data[median_index]);
            medians++;
        }

        return select(data, begin, begin + medians);
    }
    static T mom(std::vector<T>& data, size_t k, size_t begin, size_t end) {
        size_t pivot_index = select(data, begin, end);
        
        pivot_index = partition(data, pivot_index, begin, end);

        if (pivot_index == k) {
            return data[pivot_index];
        }
        else if (pivot_index > k) {
            return mom(data, k, begin, pivot_index);
        } else {
            return mom(data, k, pivot_index + 1, end);
        }
    }
public:
    static T median_of_medians_select(const std::vector<T>& data, size_t k) {
        auto cpy = data;
        return mom(cpy, k, 0, cpy.size());
    }
};