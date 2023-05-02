#ifndef COMBINATIONS_SUM_HPP
#define COMBINATIONS_SUM_HPP
#include <vector>
#include <iostream>
#include <gtest/gtest.h>

/**
 * 给定一组正整数（无重复），求解元素组合，使它们的和等于给定值。返回所有可能的组合，每个元素在一个组合中只能使用一次。
 * 
 * 注意：
 *     1. 如果备选数字中，有重复数字，则可先排序，去除重复元素后，再求解。
 *     2. 如果备选数字中，有负数，则不能剪枝
*/
class CombinationSum
{
public:
    static std::vector<std::vector<int>> Solution(const std::vector<int>& candidates, int target)
    {
        if (candidates.size() == 0)
            throw std::invalid_argument("data size is 0");

        
        std::vector<std::vector<int>> subsets;
        std::vector<bool> selected_pos(candidates.size());
        int sum = 0;
        GetSubsets(candidates, 0, selected_pos, subsets, sum, target);

        return subsets;
    }

    static void TestByCase(std::vector<int> candidates, int target, std::vector<std::vector<int>> ans)
    {
        std::vector<std::vector<int>> result = Solution(candidates, target);

        EXPECT_EQ(result.size(), ans.size());

        for (size_t i = 0, size_1 = ans.size(); i < size_1; i++)
        {
            EXPECT_EQ(result[i].size(), ans[i].size());

            for (size_t j = 0, size_2 = ans[i].size(); j < size_2; j++)
            {
                EXPECT_EQ(ans[i][j], result[i][j]);
            }
        }
    }

    static void Test()
    {
        std::cout << "test_combination_sum..." << std::endl;
        TestByCase({1, 2, 3, 4, 5, 6}, 7, {{1, 2, 4}, {1, 6}, {2, 5}, {3, 4}});  
    }

private:
    static void GetSubsets(const std::vector<int>& candidates, size_t index, std::vector<bool>& selected_pos, std::vector<std::vector<int>>& subsets, int& sum, const int& target)
    {
        if (index == candidates.size())
        {
            if (sum == target)
            {
                std::vector<int> subset;
                for (size_t i = 0, size = candidates.size(); i < size; i++)
                {
                    if (selected_pos[i])
                        subset.push_back(candidates[i]);
                }

                if (subset.size() > 0)
                    subsets.push_back(subset);
            }
        }
        else
        {
            if (sum + candidates[index] <= target)
            {
                selected_pos[index] = true;
                sum += candidates[index];
                GetSubsets(candidates, index + 1, selected_pos, subsets, sum, target);

                selected_pos[index] = false;
                sum -= candidates[index];
            }

            // 记录剩余的数字和，可以作右剪枝
            GetSubsets(candidates, index + 1, selected_pos, subsets, sum, target);
        }
    }

};

#endif