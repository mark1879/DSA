#include "subset_tree.hpp"
#include <gtest/gtest.h>

void TestSelectNumbersByCase(const SubsetTree& subset_tree, std::vector<int> data, unsigned int min_diff)
{
    std::vector<bool> selected_pos(data.size());
    EXPECT_EQ(subset_tree.SelectNumbers(data, selected_pos), min_diff);
}

void TestSelectNumbers()
{
    std::cout << "test_select_numbers..." << std::endl;

    SubsetTree subset_tree;

    TestSelectNumbersByCase(subset_tree, {10}, 10);
    TestSelectNumbersByCase(subset_tree, {10, 20}, 10);
    TestSelectNumbersByCase(subset_tree, {10, 20, 31}, 1);
    TestSelectNumbersByCase(subset_tree, {10, 20, 30, 11}, 9);
}

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

void TESTSelectNFrom2NByCase(const SubsetTree& subset_tree, std::vector<int> data, unsigned int min_diff)
{
    std::vector<bool> selected_pos(data.size());
    EXPECT_EQ(subset_tree.SelectNFrom2N(data, selected_pos), min_diff);
}

void TESTSelectNFrom2N()
{
    std::cout << "test_select_N_from_2N..." << std::endl;

    SubsetTree subset_tree;

    TESTSelectNFrom2NByCase(subset_tree, {1, 2}, 1);
    TESTSelectNFrom2NByCase(subset_tree, {1, 2, 3, 4}, 0);
    TESTSelectNFrom2NByCase(subset_tree, {1, 2, 3, 5}, 1);
    TESTSelectNFrom2NByCase(subset_tree, {1, 3, 3, 5}, 0);
}

int main()
{
    std::cout << "test_back_tracking..." << std::endl;

    TestSelectNumbers();
    TestGetSubsets();
    TESTSelectNFrom2N();
   
    std::cout << "test done!" << std::endl << std::endl;

    return 0;
}