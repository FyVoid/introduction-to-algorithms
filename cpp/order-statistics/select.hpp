#pragma once

#include <concepts>
#include <vector>
#include <tuple>
#include <algorithm>

template<std::totally_ordered T>
class SelectionAlgorithm {
public:
    static std::vector<T> shuffle(const std::vector<T>& data) {
        auto ret = data;
        for (size_t i = 0; i < ret.size(); i++) {
            auto j = get_rand<size_t>(0, ret.size() - 1);
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
    static std::tuple<size_t, T> linear_select(const std::vector<T>& data, size_t k) {
        auto cpy = data;
        std::sort(cpy.begin(), cpy.end());
        return {k, cpy[k]};
    }
private:
    static size_t random_partition(std::vector<T>& data, size_t begin, size_t end) {
        auto pivot_index = get_rand<size_t>(begin, end - 1);
        std::swap(data[begin], data[pivot_index]);

        auto pivot = data[begin];
        auto left = begin + 1;
        auto right = end - 1;

        while (true) {
            while (data[left] < pivot) {
                left++;
            }
            while (data[right] > pivot) {
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
    static std::tuple<size_t, T> rselect(std::vector<T>& data, size_t k, size_t begin, size_t end) {
        auto partition = random_partition(data, begin, end);
        if (partition == k) {
            return {partition, data[partition]};
        }
        else if (partition > k) {
            return rselect(data, k, begin, partition);
        } else {
            return rselect(data, k, partition + 1, end);
        }
    }
public:
    // return k-th smallest element and its index in the original array
    static std::tuple<size_t, T> random_select(const std::vector<T>& data, size_t k) {
        auto cpy = data;
        return rselect(cpy, k, 0, cpy.size());
    }
};