#include "singly_linked_list.hpp"
#include <gtest/gtest.h>

#define MAX_SIZE 10

void check_elements(SinglyLinkedList<int>& linked_list, bool results) {
    for (unsigned int i = 0; i < MAX_SIZE; i++) 
        EXPECT_EQ(linked_list.Find(i), results);
}

int main() {

    cout << endl << "test_singly_linked_list..." << endl;

    SinglyLinkedList<int> linked_list;

    // PushBack
    for (unsigned int i = 0; i < MAX_SIZE; i++) {
        linked_list.PushBack(i);
        EXPECT_EQ(linked_list.size(), i + 1);
        EXPECT_EQ(linked_list.Find(i), true);
    }

    linked_list.PushBack(100);
    EXPECT_EQ(linked_list.size(), MAX_SIZE + 1);
    EXPECT_EQ(linked_list.Find(100), true);
    check_elements(linked_list, true);


    // PopBack
    linked_list.PopBack();
    EXPECT_EQ(linked_list.size(), MAX_SIZE);
    EXPECT_EQ(linked_list.Find(100), false);
    check_elements(linked_list, true);


    // PushFront
    linked_list.PusFront(100);
    EXPECT_EQ(linked_list.Find(100), true);
    EXPECT_EQ(linked_list.size(), MAX_SIZE + 1);
    check_elements(linked_list, true);


    // PopFront
    linked_list.PopFront();
    EXPECT_EQ(linked_list.Find(100), false);
    EXPECT_EQ(linked_list.size(), MAX_SIZE);
    check_elements(linked_list, true);


    // Insert
    linked_list.Insert(0, 100);
    EXPECT_EQ(linked_list.Find(100), true);
    EXPECT_EQ(linked_list.size(), MAX_SIZE + 1);
    check_elements(linked_list, true);


    // Remove
    linked_list.Remove(100);
    EXPECT_EQ(linked_list.Find(100), false);
    EXPECT_EQ(linked_list.size(), MAX_SIZE);
    check_elements(linked_list, true);

    // Clear
    linked_list.Clear();
    EXPECT_EQ(linked_list.size(), 0);
    check_elements(linked_list, false);

    cout << "test done!" << endl << endl;

    return 0;
}