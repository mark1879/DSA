/*
    整形数组，把偶数调整到数组的左边，把奇数调整到数组的右边
*/

#include <iostream>
#include <vector>
#include <gtest/gtest.h>

using namespace std;

void AdjustArray(vector<int>& vec) {
    size_t size = vec.size();
    if (size <= 1)
        return;

    size_t left = 0;
    size_t right = size - 1;

    while (left < right) {
        while (left < right) {
            if ((vec[left] & 0x1) == 1)
                break;
            
            ++left;
        }

        while (left < right) {
            if ((vec[right] & 0x1) == 0)
                break;

            --right;
        }

        if (left < right) {
            int tmp = vec[left];
            vec[left] = vec[right];
            vec[right] = tmp;

            ++left;
            --right;
        }
    }
}

int main() {

    cout << endl << "<<<<<< test adjust_array..." << endl;

    vector<int> vec = {1, 2};
    AdjustArray(vec);
    EXPECT_EQ(vec[0], 2);
    EXPECT_EQ(vec[1], 1);

    vector<int> vec1 = {1, 2, 1, 2, 2, 1};
    AdjustArray(vec1);
    EXPECT_EQ(vec1[0], 2);
    EXPECT_EQ(vec1[1], 2);
    EXPECT_EQ(vec1[2], 2);
    EXPECT_EQ(vec1[3], 1);
    EXPECT_EQ(vec1[4], 1);
    EXPECT_EQ(vec1[5], 1);

    cout << "done!" << endl << endl;

    return 0;
}