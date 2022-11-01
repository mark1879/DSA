#include "linked_list.hpp"
#include <gtest/gtest.h>

int main() {

    cout << endl << "test_linked_list..." << endl;

    LinkedList<int> linked_list;

    for (int i = 0; i < 10; i++) {
        linked_list.PushBack(i);
        EXPECT_EQ(linked_list.size(), i + 1);
        EXPECT_EQ(linked_list.Find(i), true);
    }

    for (int i = 9; i >= 0; i--) {
        linked_list.PopBack();
        EXPECT_EQ(linked_list.size(), i);
        EXPECT_EQ(linked_list.Find(i), false);
    }

    cout << "test done!" << endl << endl;

    return 0;
}