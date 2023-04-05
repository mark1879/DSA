#ifndef SUBSET_TREE_SELECT_NUMBERS_HPP
#define SUBSET_TREE_SELECT_NUMBERS_HPP

#include <iostream>
#include <vector>

class GetSubsets
{
public:
    /**
        使用给定的整数集合(不重复)，生成全部的子集。
    */
    void  GetSubsets(const std::vector<int>& data, std::vector<std::vector<int>>& subsets) const
    {
         if (data.size() == 0)
            throw std::invalid_argument("data size is 0");

        std::vector<bool> selected_pos(data.size());
        GetSubsets(data, 0, selected_pos, subsets);
    }

private:
    void GetSubsets(const std::vector<int>& data, size_t index, std::vector<bool> selected_pos, std::vector<std::vector<int>>& subsets) const
    {
        if (index == data.size())
        {
            std::vector<int> subset;
            for (size_t i = 0, size = data.size(); i < size; i++)
            {
                if (selected_pos[i])
                    subset.push_back(data[i]);
            }

            if (subset.size() > 0)
                subsets.push_back(subset);
        }
        else
        {
            selected_pos[index] = true;
            GetSubsets(data, index + 1, selected_pos, subsets);

            selected_pos[index] = false;
            GetSubsets(data, index + 1, selected_pos, subsets);
        }
    }
};

void TestGetSubsetsByCase(const SubsetTree& subset_tree, std::vector<int> data, std::vector<std::vector<int>> ans)
{
    std::vector<std::vector<int>> result;
    subset_tree.GetSubsets(data, result);

    EXPECT_EQ(result.size(), ans.size());

    for (size_t i = 0, size1 = result.size(); i < size1; i++)
    {
        EXPECT_EQ(result[i].size(), ans[i].size());

        for (size_t j = 0, size2 = result[i].size(); j < size2; j++)
        {
            EXPECT_EQ(result[i][j], ans[i][j]);
        }
    }
}

void TestGetSubsets()
{
    std::cout << "test_get_subsets" << std::endl;

    SubsetTree subset_tree;
    TestGetSubsetsByCase(subset_tree, {1}, {{1}});
    TestGetSubsetsByCase(subset_tree, {1, 2}, {{1, 2}, {1}, {2}});
    TestGetSubsetsByCase(subset_tree, {1, 2, 3}, {{1, 2, 3}, {1, 2}, {1, 3}, {1}, {2, 3}, {2}, {3}});
}

#endif