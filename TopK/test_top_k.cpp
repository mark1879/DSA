#include <iostream>
#include <algorithm>
#include <functional>
#include <gtest/gtest.h>
#include "top_k_by_heap.hpp"
#include "tok_k_by_quick_sort_partition.hpp"

using GET_TOP_K_MIN_NUMS = std::function<std::vector<int>(std::vector<int>&, size_t)>;

void TestGetTopKMinNums(GET_TOP_K_MIN_NUMS solution, std::vector<int> data, size_t k, std::vector<int> ans)
{
    std::vector<int> top_k_min_nums = solution(data, k);
    EXPECT_EQ(top_k_min_nums.size(), ans.size());

    std::sort(top_k_min_nums.begin(), top_k_min_nums.end());

    for (size_t i = 0, size = ans.size(); i < size; i++)
    {
        EXPECT_EQ(ans[i], top_k_min_nums[i]);
    }
}

void TestGetTopKMinNums()
{

    TopKByHeap top_k_by_heap;

    TestGetTopKMinNums(std::bind(&TopKByHeap::GetTopKMinNums, top_k_by_heap, std::placeholders::_1, std::placeholders::_2)
                                    , {5, 4, 3, 2, 1}, 3, {1, 2, 3});
    TestGetTopKMinNums(std::bind(&TopKByHeap::GetTopKMinNums, top_k_by_heap, std::placeholders::_1, std::placeholders::_2)
                                    , {1, 2, 3, 4, 5}, 3, {1, 2, 3});

    TestGetTopKMinNums(std::bind(&TopKByHeap::GetTopKMinNums2, top_k_by_heap, std::placeholders::_1, std::placeholders::_2)
                                    , {5, 4, 3, 2, 1}, 3, {1, 2, 3});
    TestGetTopKMinNums(std::bind(&TopKByHeap::GetTopKMinNums2, top_k_by_heap, std::placeholders::_1, std::placeholders::_2)
                                    , {1, 2, 3, 4, 5}, 3, {1, 2, 3});

    // 统计重复次数最小的前 k 个数字
    TestGetTopKMinNums(std::bind(&TopKByHeap::GetTopKMinRepetitionNums, top_k_by_heap, std::placeholders::_1, std::placeholders::_2)
                                    , {5, 5, 4, 4, 3, 3, 3, 2, 2, 2, 2, 1, 1, 1}, 3, {3, 4, 5});

    TopKByQSP top_k_by_qsp;
    TestGetTopKMinNums(std::bind(&TopKByQSP::GetTopKMinNums, top_k_by_qsp, std::placeholders::_1, std::placeholders::_2)
                                        , {5, 4, 3, 2, 1}, 3, {1, 2, 3});
    TestGetTopKMinNums(std::bind(&TopKByQSP::GetTopKMinNums, top_k_by_qsp, std::placeholders::_1, std::placeholders::_2)
                                    , {1, 2, 3, 4, 5}, 3, {1, 2, 3});
    TestGetTopKMinNums(std::bind(&TopKByQSP::GetTopKMinNums, top_k_by_qsp, std::placeholders::_1, std::placeholders::_2)
                                    , {0, 5, 4, 0, 3, 2, 1, 6}, 3, {0, 0, 1});
}

int main()
{
    std::cout << "test_top_k..." << std::endl;

    TestGetTopKMinNums();

    std::cout << "test done!" << std::endl;

    return 0;
}