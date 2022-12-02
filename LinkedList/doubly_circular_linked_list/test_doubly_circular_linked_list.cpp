#include "doubly_circular_linked_list.hpp"
#include <gtest/gtest.h>

#define MAX_SIZE 10

void check_elements(DoublyCircularLinkedList<int>& linked_list, bool results) {
    for (unsigned int i = 0; i < MAX_SIZE; i++) {
        EXPECT_EQ(linked_list.Find(i), results);
        EXPECT_EQ(linked_list.RFind(i), results);
    }
}

int main() {

    cout << "<<<<<< test_doubly_circular_linked_list..." << endl;

    DoublyCircularLinkedList<int> linked_list;

    // PushBack
    for (unsigned int i = 0; i < MAX_SIZE; i++) {
        linked_list.PushBack(i);
        EXPECT_EQ(linked_list.size(), i + 1);
        EXPECT_EQ(linked_list.Find(i), true);
        EXPECT_EQ(linked_list.RFind(i), true);
        EXPECT_EQ(linked_list.IsDoublyCircular(), true);
    }

    linked_list.PushBack(100);
    EXPECT_EQ(linked_list.size(), MAX_SIZE + 1);
    EXPECT_EQ(linked_list.Find(100), true);
    EXPECT_EQ(linked_list.RFind(100), true);
    EXPECT_EQ(linked_list.IsDoublyCircular(), true);
    check_elements(linked_list, true);


    // PopBack
    linked_list.PopBack();
    EXPECT_EQ(linked_list.size(), MAX_SIZE);
    EXPECT_EQ(linked_list.Find(100), false);
    EXPECT_EQ(linked_list.RFind(100), false);
    EXPECT_EQ(linked_list.IsDoublyCircular(), true);
    check_elements(linked_list, true);


    // PushFront
    linked_list.PusFront(100);
    EXPECT_EQ(linked_list.Find(100), true);
    EXPECT_EQ(linked_list.RFind(100), true);
    EXPECT_EQ(linked_list.size(), MAX_SIZE + 1);
    EXPECT_EQ(linked_list.IsDoublyCircular(), true);
    check_elements(linked_list, true);


    // PopFront
    linked_list.PopFront();
    EXPECT_EQ(linked_list.Find(100), false);
    EXPECT_EQ(linked_list.RFind(100), false);
    EXPECT_EQ(linked_list.size(), MAX_SIZE);
    EXPECT_EQ(linked_list.IsDoublyCircular(), true);
    check_elements(linked_list, true);

    // Remove
    linked_list.Remove(0);
    EXPECT_EQ(linked_list.Find(0), false);
    EXPECT_EQ(linked_list.RFind(0), false);
    EXPECT_EQ(linked_list.size(), MAX_SIZE - 1);
    linked_list.Remove(9);
    EXPECT_EQ(linked_list.Find(9), false);
    EXPECT_EQ(linked_list.RFind(9), false);
    EXPECT_EQ(linked_list.size(), MAX_SIZE - 2);
     linked_list.Remove(5);
    EXPECT_EQ(linked_list.Find(5), false);
    EXPECT_EQ(linked_list.RFind(5), false);
    EXPECT_EQ(linked_list.size(), MAX_SIZE - 3);
    EXPECT_EQ(linked_list.IsDoublyCircular(), true);


    // Clear
    linked_list.Clear();
    EXPECT_EQ(linked_list.size(), 0);
    check_elements(linked_list, false);
    EXPECT_EQ(linked_list.IsDoublyCircular(), true);

    cout << "test done!" << endl << endl;
    
    return 0;
}