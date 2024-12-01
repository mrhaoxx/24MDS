#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono> 
#include <random> 

#include "HeapSort.h"

// 检查排序是否正确
bool check(const std::vector<int>& nums) {
    for (size_t i = 1; i < nums.size(); ++i) {
        if (nums[i - 1] > nums[i]) {
            return false;
        }
    }
    return true;
}

// 生成测试序列
std::vector<int> generateRandomSequence(size_t size) {
    std::vector<int> nums(size);
    std::mt19937 rng(std::random_device{}());
    std::uniform_int_distribution<int> dist(1, 1000000);
    std::generate(nums.begin(), nums.end(), [&]() { return dist(rng); });
    return nums;
}

std::vector<int> generateSortedSequence(size_t size) {
    std::vector<int> nums(size);
    for (size_t i = 0; i < size; ++i) {
        nums[i] = i + 1;
    }
    return nums;
}

std::vector<int> generateReverseSequence(size_t size) {
    std::vector<int> nums(size);
    for (size_t i = 0; i < size; ++i) {
        nums[i] = size - i;
    }
    return nums;
}

std::vector<int> generatePartiallyDuplicateSequence(size_t size) {
    std::vector<int> nums(size);
    std::mt19937 rng(std::random_device{}());
    std::uniform_int_distribution<int> dist(1, size / 10);
    std::generate(nums.begin(), nums.end(), [&]() { return dist(rng); });
    return nums;
}

// 测试函数
void testHeapSort(const std::string& testName, std::vector<int>& nums) {
    std::vector<int> copy1 = nums;
    std::vector<int> copy2 = nums;

    // 使用自定义堆排序
    auto start = std::chrono::high_resolution_clock::now();
    heapSort(copy1);
    auto end = std::chrono::high_resolution_clock::now();
    auto customDuration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

    // 检查结果
    if (!check(copy1)) {
        std::cerr << testName << " 自定义堆排序失败！" << std::endl;
        return;
    }

    // 使用 std::sort_heap
    start = std::chrono::high_resolution_clock::now();
    std::make_heap(copy2.begin(), copy2.end());
    std::sort_heap(copy2.begin(), copy2.end());
    end = std::chrono::high_resolution_clock::now();
    auto stlDuration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

    if (!check(copy2)) {
        std::cerr << testName << " STL 堆排序失败！" << std::endl;
        return;
    }

    // 输出测试结果
    std::cout << testName << ": 自定义堆排序时间 = " << customDuration
              << "ms, STL 堆排序时间 = " << stlDuration << "ms" << std::endl;
}

int main() {
    size_t testSize = 10000000;

    // 测试随机序列
    auto randomSequence = generateRandomSequence(testSize);
    testHeapSort("随机序列", randomSequence);

    // 测试有序序列
    auto sortedSequence = generateSortedSequence(testSize);
    testHeapSort("有序序列", sortedSequence);

    // 测试逆序序列
    auto reverseSequence = generateReverseSequence(testSize);
    testHeapSort("逆序序列", reverseSequence);

    // 测试部分重复的序列
    auto partiallyDuplicateSequence = generatePartiallyDuplicateSequence(testSize);
    testHeapSort("部分重复序列", partiallyDuplicateSequence);

    return 0;
}