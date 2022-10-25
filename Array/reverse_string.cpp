#include <iostream>
#include <gtest/gtest.h>

using namespace std;

void Reverse(string& str) {
    size_t size = str.size();

    if (size <= 1)
        return;

    size_t left = 0;
    size_t right = size - 1;

    while (left < right) {
        char tmp = str[left];
        str[left] = str[right];
        str[right] = tmp;

        ++left;
        --right;
    }
}

int main() {

    cout << endl << "test reverse_string..." << endl;

    string str = "I";
    Reverse(str);
    EXPECT_EQ(str, "I");

    str = "We";
    Reverse(str);
    EXPECT_EQ(str, "eW");

    str = "His";
    Reverse(str);
    EXPECT_EQ(str, "siH");

    cout << "done!" << endl << endl;

    return 0;
}