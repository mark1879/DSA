#include <iostream>
#include <chrono>
#include <algorithm>
#include <gtest/gtest.h>
#include "bubble_sort.hpp"
#include "quick_sort.hpp"
#include "heap_sort.hpp"

int* GenerateTestData(int size_of_data)
{
    int *data = (int *)malloc(size_of_data * sizeof(int));
    EXPECT_NE(data, nullptr);

    memset(data, 0, size_of_data * sizeof(int));

    srand((unsigned) time(nullptr));
    for (int i = 0; i < size_of_data; i++)
    {
        data[i] = rand() % size_of_data;
    }

    return data;
}

void Test(const char* sort_name, const int* data, int size_of_data, bool(*sort_func)(int *, int)) 
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

    for (int i = 0; i < size_of_data - 1; i++)
        EXPECT_EQ(copy_of_data[i] <= copy_of_data[i + 1], true);

    free(copy_of_data);

    std::cout << "test done!" << std::endl << std::endl;
}


void TestStdSort(std::vector<int>& data)
{
    std::chrono::milliseconds start_time = std::chrono::duration_cast< std::chrono::milliseconds >(
            std::chrono::system_clock::now().time_since_epoch());

    std::sort(data.begin(), data.end(), std::less<int>());

    std::chrono::milliseconds end_time = std::chrono::duration_cast< std::chrono::milliseconds >(
            std::chrono::system_clock::now().time_since_epoch());

    std::cout << "test std::sort..." << std::endl;
    std::cout << "time consumed: " << (end_time.count() - start_time.count()) << "ms" << std::endl;

    for (int i = 0, size_of_data = data.size(); i < size_of_data - 1; i++)
        EXPECT_EQ(data[i] <= data[i + 1], true);
}

int main()
{
    std::cout << "test sort algorithms..." << std::endl << std::endl;

    int size_of_data = 1000 * 30;

    int* data = GenerateTestData(size_of_data);

    // Test the stability of the sorting algorithm
    for (int i = 0; i < size_of_data; i++)
        data[i] = size_of_data - i;

    Test("bubble sort", data, size_of_data, (bool(*)(int *, int))BubbleSort);

    Test("quick sort", data, size_of_data, (bool(*)(int*, int))QuickSort);

    Test("quick sort2", data, size_of_data, (bool(*)(int*, int))QuickSort2);

    Test("heap sort", data, size_of_data, (bool(*)(int*, int))HeapSort);

    std::vector<int> vec_data;
    for (int i = 0; i < size_of_data; i++)
        vec_data.push_back(data[i]);
        
    TestStdSort(vec_data);

    free(data);

    std::cout << "test done!" << std::endl << std::endl;

    return 0;
}