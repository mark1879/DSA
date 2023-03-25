#include "subset_tree_select_numbers.hpp"
#include <gtest/gtest.h>

void TestSubsetTreeSelectNumbers(std::vector<int> data, unsigned int min_diff)
{
    std::vector<bool> selected_pos(data.size());
    SelectNumbers selected_numbers;
    EXPECT_EQ(selected_numbers.GetMinDiff(data, selected_pos), min_diff);
}

int main()
{
    std::cout << "test_back_tracking..." << std::endl;

    TestSubsetTreeSelectNumbers({10}, 10);
    TestSubsetTreeSelectNumbers({10, 20}, 10);
    TestSubsetTreeSelectNumbers({10, 20, 31}, 1);
    TestSubsetTreeSelectNumbers({10, 20, 30, 11}, 9);

    std::cout << "test done!" << std::endl << std::endl;

    return 0;
}