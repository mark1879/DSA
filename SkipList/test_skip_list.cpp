#include "skip_list.hpp"
#include <gtest/gtest.h>

int main()
{
    std::cout << "test_skip_list..." << std::endl;

    SkipList<int> skip_list;

    for (int i = 1; i <= 20; i++)
    {
        skip_list.Add(i, i);
        Node<int>* iter = skip_list.Find(i);
        EXPECT_NE(iter, nullptr);
        EXPECT_EQ(iter->key_, i);
    }

    for (int i = 1; i <= 20; i++)
    {
        skip_list.Delete(i);
        EXPECT_EQ(skip_list.Find(i), nullptr);
    }



    std::cout << "test done!" << std::endl;

    return 0;
}