#include <iostream>
#include <gtest/gtest.h>
#include "bitmap.hpp"
#include "bloom_filter.hpp"

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

void TestBloomFilter()
{
    std::cout << "test_bloom_filter..." << std::endl;
    std::vector<std::string> white_list = {
        "www.baidu.com",
        "www.qq.com",
        "www.zhihu.com"
    };

    BloomFilter bloom_filter; 

    for (const auto& it : white_list)
    {
        bloom_filter.SetBit(it);
        EXPECT_EQ(bloom_filter.GetBit(it), true);
    }

    std::string black_url = "www.google.com";
    EXPECT_EQ(bloom_filter.GetBit(black_url), false);
}

int main()
{
    std::cout << "test_massive_data_deduplication..." << std::endl;

    TestBitmap();
    TestBloomFilter();

    std::cout << "test done!" << std::endl << std::endl;

    return 0;
}