#include <iostream>
#include <chrono>
#include <gtest/gtest.h>
#include "bubble_sort.hpp"
#include "quick_sort.hpp"

int* GenerateTestData(unsigned int size_of_data)
{
    int *data = (int *)malloc(size_of_data * sizeof(int));
    EXPECT_NE(data, nullptr);

    memset(data, 0, size_of_data * sizeof(int));

    srand((unsigned) time(nullptr));
    for (unsigned i = 0; i < size_of_data; i++)
    {
        data[i] = rand() % size_of_data;
    }

    return data;
}

void Test(const char* sort_name, const int* data, unsigned int size_of_data, bool(*sort_func)(int *, unsigned int)) 
{
    std::cout << "test " << sort_name << "..." << std::endl;

    int *copy_of_data = (int *)malloc(size_of_data * sizeof(int));
    EXPECT_NE(copy_of_data, nullptr);

    memcpy(copy_of_data, data, size_of_data * sizeof(int));

    std::chrono::milliseconds start_time = std::chrono::duration_cast< std::chrono::milliseconds >(
            std::chrono::system_clock::now().time_since_epoch());

    EXPECT_EQ(sort_func(copy_of_data, size_of_data), true);

    std::chrono::milliseconds end_time = std::chrono::duration_cast< std::chrono::milliseconds >(
            std::chrono::system_clock::now().time_since_epoch());

    std::cout << "time consumed: " << (end_time.count() - start_time.count()) << "ms" << std::endl;

    for (unsigned i = 0; i < size_of_data - 1; i++)
        EXPECT_EQ(copy_of_data[i] <= copy_of_data[i + 1], true);

    free(copy_of_data);

    std::cout << "test done!" << std::endl << std::endl;
}

int main()
{
    std::cout << "test sort algorithms:" << std::endl << std::endl;

    unsigned int size_of_data = 1000 * 100;

    int* data = GenerateTestData(size_of_data);

    Test("bubble sort", data, size_of_data, (bool(*)(int *, unsigned int))bubble_sort);

    Test("quick sort", data, size_of_data, (bool(*)(int*, unsigned int))quick_sort);

    free(data);

    return 0;
}