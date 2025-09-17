#include "sorting.hpp"
#include "helper.hpp"
#include <algorithm>

template <typename T>
void check_vector_equal(const std::vector<T>& a, const std::vector<T>& b) {
    if (a.size() != b.size()) {
        throw std::runtime_error("Vectors have different sizes");
    }
    for (size_t i = 0; i < a.size(); i++) {
        if (a[i] != b[i]) {
            throw std::runtime_error("Vectors are not equal");
        }
    }
    std::cout << "Check passed: Vectors are equal." << std::endl;
}

int main() {
    auto data = SortingAlgorithm<int>::makeData(10000);
    auto standard = data;
    std::sort(standard.begin(), standard.end());
    time_it([data, standard]() {
        auto sorted = SortingAlgorithm<int>::insertionSort(data);
        check_vector_equal(standard, sorted);
    }, "Insertion Sort");
    time_it([data, standard]() {
        auto sorted = SortingAlgorithm<int>::bubbleSort(data);
        check_vector_equal(standard, sorted);
    }, "Bubble Sort");
    time_it([data, standard]() {
        auto sorted = SortingAlgorithm<int>::mergeSort(data);
        check_vector_equal(standard, sorted);
    }, "Merge Sort");
    time_it([data, standard]() {
        auto sorted = SortingAlgorithm<int>::heapSort(data);
        check_vector_equal(standard, sorted);
    }, "Heap Sort");
    time_it([data, standard]() {
        auto sorted = SortingAlgorithm<int>::quickSort(data);
        check_vector_equal(standard, sorted);
    }, "Quick Sort");
    time_it([data, standard]() {
        auto sorted = SortingAlgorithm<int>::countingSort(data, data.size());
        check_vector_equal(standard, sorted);
    }, "Counting Sort");
    time_it([data, standard]() {
        auto sorted = SortingAlgorithm<int>::radixSort(data);
        check_vector_equal(standard, sorted);
    }, "Radix Sort");
    time_it([data, standard]() {
        auto sorted = SortingAlgorithm<int>::bucketSort(data, 10);
        check_vector_equal(standard, sorted);
    }, "Bucket Sort");
    return 0;
}