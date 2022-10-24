#include "array.hpp"
#include <gtest/gtest.h>
#include <iostream>

using namespace std;

void show_arr(Array<long>& arr) {
    for (int i = 0; i < arr.size(); i++) {
        long val;
        arr.get(i, val);
        cout << val << "\t ";
    }
    cout << endl;
}

int main() {

    cout << endl << "test_array..." << endl;

    Array<long> arr;
    for (int i = 0; i < 20; i++) {
        arr.push_back(i);   

        EXPECT_EQ(arr.size(), i + 1);
        EXPECT_EQ(arr.capacity(), (i / 10 + 1) * 10);
    }

    show_arr(arr);

    // pop_back
    int old_size = arr.size();
    arr.pop_back();
    EXPECT_EQ(arr.size(), old_size - 1);


    // insert
    old_size = arr.size();
    arr.insert(1, 100);

    long val;
    arr.get(1, val);
    EXPECT_EQ(val, 100);
    EXPECT_EQ(arr.size(), old_size + 1);
    

    // earse
    old_size = arr.size();
    arr.erase(1);
    EXPECT_EQ(arr.size(), old_size - 1);

    long val1;
    arr.get(1, val);
    EXPECT_NE(val, 100);

    cout << "done!" << endl << endl;
    
    return 0;
}