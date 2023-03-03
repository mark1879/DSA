#include <iostream>
#include <gtest/gtest.h>
#include "binary_search.hpp"

void TestCase(const int data[], int size_of_data, int value, int ans, int(*func)(const int *, int, int))
{
    EXPECT_EQ(func(data, size_of_data, value), ans);
    EXPECT_EQ(func(data, size_of_data, value), ans);
}

int main()
{
    std::cout << "test_binary_search..." << std::endl;

    const int size = 10;
    const int data[size] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

    TestCase(data, size, 0, 0, (int(*)(const int *, int, int))binary_search);
    TestCase(data, size, 0, 0, (int(*)(const int *, int, int))bianry_search_recursively);

    TestCase(data, size, 9, 9, (int(*)(const int *, int, int))binary_search);
    TestCase(data, size, 9, 9, (int(*)(const int *, int, int))bianry_search_recursively);

    TestCase(data, size, 5, 5, (int(*)(const int *, int, int))binary_search);
    TestCase(data, size, 5, 5, (int(*)(const int *, int, int))bianry_search_recursively);


    TestCase(data, size, 10, -1, (int(*)(const int *, int, int))binary_search);
    TestCase(data, size, 10, -1, (int(*)(const int *, int, int))bianry_search_recursively);

    std::cout << "test done!" << std::endl;

    return 0;
}