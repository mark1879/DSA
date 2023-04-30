#include "vector.hpp"
#include <gtest/gtest.h>

using namespace DSA;

int main()
{
    std::cout << "test_vector..." << std::endl;

    Vector<int> vec;

    EXPECT_EQ(vec.empty(), true);

    vec.push_back(1);
    EXPECT_EQ(vec.empty(), false);
    EXPECT_EQ(vec.size(), 1);
    EXPECT_EQ(vec[0], 1);

    int front = vec.front();
    EXPECT_EQ(front, 1);

    int& reference_fornt = vec.front();
    reference_fornt = 2;
    EXPECT_EQ(vec[0], 2);

    int back = vec.back();
    EXPECT_EQ(back, 2);

    int& reference_back = vec.back();
    reference_back = 3;
    EXPECT_EQ(vec[0], 3);

    for (size_t i = 0; i < 100; i++)
        vec.push_back(i);

    Vector<int> vec_cpy = vec;
    // for (size_t i = 0; i < 100; i++)
    //     vec_cpy.pop_back();

    Vector<int> vec_move = std::move(vec);
    for (size_t i = 0; i < 100; i++)
        vec_move.pop_back();

    std::cout << "test done!" << std::endl << std::endl;

    return 0;
}