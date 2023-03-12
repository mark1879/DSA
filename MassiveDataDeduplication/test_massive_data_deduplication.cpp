#include "bitmap.hpp"
#include <iostream>
#include <gtest/gtest.h>

void TestBitmap()
{
    std::cout << "test_bitmap..." << std::endl;
    std::vector<unsigned int> keys = {12, 78, 90, 78, 123, 8, 9, 90};
    Bitmap bitmap(keys);

    EXPECT_EQ(bitmap.Exist(12), true);
    EXPECT_EQ(bitmap.Exist(0), false);


    std::vector<unsigned int> keys1 = {0, 0, 0, 0, 0, 0};
    Bitmap bitmap1(keys1);
    EXPECT_EQ(bitmap1.Exist(12), false);
    EXPECT_EQ(bitmap1.Exist(0), true);
}

int main()
{
    std::cout << "test_massive_data_deduplication..." << std::endl;

    TestBitmap();

    std::cout << "test done!" << std::endl << std::endl;

    return 0;
}