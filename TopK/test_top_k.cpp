#include <iostream>
#include <algorithm>
#include <functional>
#include <gtest/gtest.h>
#include "top_k_by_heap.hpp"
#include "tok_k_by_quick_sort_partition.hpp"

using GET_TOP_K_MIN_NUMS = std::function<std::vector<int>(std::vector<int>&, size_t)>;

void TestGetTopKMinNumsByCase(GET_TOP_K_MIN_NUMS solution, std::vector<int> data, size_t k, std::vector<int> ans)
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
    TestGetTopKMinNumsByCase(std::bind(&TopKByHeap::GetTopKMinNums, top_k_by_heap, std::placeholders::_1, std::placeholders::_2)
                                    , {5, 4, 3, 2, 1}, 3, {1, 2, 3});
    TestGetTopKMinNumsByCase(std::bind(&TopKByHeap::GetTopKMinNums, top_k_by_heap, std::placeholders::_1, std::placeholders::_2)
                                    , {1, 2, 3, 4, 5}, 3, {1, 2, 3});

    TestGetTopKMinNumsByCase(std::bind(&TopKByHeap::GetTopKMinNums2, top_k_by_heap, std::placeholders::_1, std::placeholders::_2)
                                    , {5, 4, 3, 2, 1}, 3, {1, 2, 3});
    TestGetTopKMinNumsByCase(std::bind(&TopKByHeap::GetTopKMinNums2, top_k_by_heap, std::placeholders::_1, std::placeholders::_2)
                                    , {1, 2, 3, 4, 5}, 3, {1, 2, 3});

    TopKByQSP top_k_by_qsp;
    TestGetTopKMinNumsByCase(std::bind(&TopKByQSP::GetTopKMinNums, top_k_by_qsp, std::placeholders::_1, std::placeholders::_2)
                                        , {5, 4, 3, 2, 1}, 3, {1, 2, 3});
    TestGetTopKMinNumsByCase(std::bind(&TopKByQSP::GetTopKMinNums, top_k_by_qsp, std::placeholders::_1, std::placeholders::_2)
                                    , {1, 2, 3, 4, 5}, 3, {1, 2, 3});
    TestGetTopKMinNumsByCase(std::bind(&TopKByQSP::GetTopKMinNums, top_k_by_qsp, std::placeholders::_1, std::placeholders::_2)
                                    , {0, 5, 4, 0, 3, 2, 1, 6}, 3, {0, 0, 1});
}

using GET_TOP_KTH_NUM = std::function<int(std::vector<int>&, size_t)>;

void TestGetTopKthNumByCase(GET_TOP_KTH_NUM solution, std::vector<int> data, size_t k, int ans)
{
    EXPECT_EQ(solution(data, k), ans);
}

void TestGetTopKthNum()
{
    TopKByQSP tok_k_by_qsp;
    TestGetTopKthNumByCase(std::bind(&TopKByQSP::GetKthMinNum, tok_k_by_qsp, std::placeholders::_1, std::placeholders::_2)
                                    , {1, 2, 3, 4, 5, 6}, 6, 6);
     TestGetTopKthNumByCase(std::bind(&TopKByQSP::GetKthMinNum, tok_k_by_qsp, std::placeholders::_1, std::placeholders::_2)
                                    , {1, 2, 3, 4, 5, 6}, 1, 1);
    TestGetTopKthNumByCase(std::bind(&TopKByQSP::GetKthMinNum, tok_k_by_qsp, std::placeholders::_1, std::placeholders::_2)
                                    , {6, 5, 4, 3, 2, 1}, 1, 1);
    TestGetTopKthNumByCase(std::bind(&TopKByQSP::GetKthMinNum, tok_k_by_qsp, std::placeholders::_1, std::placeholders::_2)
                                    , {6, 5, 4, 3, 2, 1}, 6, 6);

    TopKByHeap top_k_by_heap;
    TestGetTopKthNumByCase(std::bind(&TopKByHeap::GetKthMinNum, top_k_by_heap, std::placeholders::_1, std::placeholders::_2)
                                    , {1, 2, 3, 4, 5, 6}, 6, 6);
     TestGetTopKthNumByCase(std::bind(&TopKByHeap::GetKthMinNum, top_k_by_heap, std::placeholders::_1, std::placeholders::_2)
                                    , {1, 2, 3, 4, 5, 6}, 1, 1);
    TestGetTopKthNumByCase(std::bind(&TopKByHeap::GetKthMinNum, top_k_by_heap, std::placeholders::_1, std::placeholders::_2)
                                    , {6, 5, 4, 3, 2, 1}, 1, 1);
    TestGetTopKthNumByCase(std::bind(&TopKByHeap::GetKthMinNum, top_k_by_heap, std::placeholders::_1, std::placeholders::_2)
                                    , {6, 5, 4, 3, 2, 1}, 6, 6);


    TestGetTopKthNumByCase(std::bind(&TopKByHeap::GetKthMinNum2, top_k_by_heap, std::placeholders::_1, std::placeholders::_2)
                                    , {1, 2, 3, 4, 5, 6}, 6, 6);
    TestGetTopKthNumByCase(std::bind(&TopKByHeap::GetKthMinNum2, top_k_by_heap, std::placeholders::_1, std::placeholders::_2)
                                    , {1, 2, 3, 4, 5, 6}, 1, 1);
    TestGetTopKthNumByCase(std::bind(&TopKByHeap::GetKthMinNum2, top_k_by_heap, std::placeholders::_1, std::placeholders::_2)
                                    , {6, 5, 4, 3, 2, 1}, 1, 1);
    TestGetTopKthNumByCase(std::bind(&TopKByHeap::GetKthMinNum2, top_k_by_heap, std::placeholders::_1, std::placeholders::_2)
                                    , {6, 5, 4, 3, 2, 1}, 6, 6);
}

int main()
{
    std::cout << "test_top_k..." << std::endl;

    TestGetTopKMinNums();
    TestGetTopKthNum();

    std::cout << "test done!" << std::endl;

    return 0;
}