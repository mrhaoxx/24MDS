#pragma once
#include <vector>
#include <algorithm>

template <typename T>
void heapSort(std::vector<T>& nums) {
    std::make_heap(nums.begin(), nums.end());

    for (auto it = nums.end(); it != nums.begin(); --it) {
        std::pop_heap(nums.begin(), it);
    }
}