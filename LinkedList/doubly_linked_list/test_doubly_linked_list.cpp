#include "doubly_linked_list.hpp"
#include <gtest/gtest.h>
#include <vector>

#define MAX_SIZE 10

void check_elements(DoublyLinkedList<int>& linked_list, vector<int>& vec, bool results) {
    for (auto ele : vec) {
        EXPECT_EQ(linked_list.Find(ele), results);
        EXPECT_EQ(linked_list.RFind(ele), results);
    }
}

int main() {

    cout << "<<<<<< test_doubly_linked_list..." << endl;

    DoublyLinkedList<int> linked_list;

    vector<int> vec;
    for (unsigned int i = 0; i < MAX_SIZE; i++) 
        vec.push_back(i);

    // PushBack
    for (unsigned int i = 0; i < MAX_SIZE; i++) {
        linked_list.PushBack(vec[i]);
        EXPECT_EQ(linked_list.size(), i + 1);
        EXPECT_EQ(linked_list.Find(vec[i]), true);
        EXPECT_EQ(linked_list.RFind(vec[i]), true);
    }

    linked_list.PushBack(100);
    EXPECT_EQ(linked_list.size(), MAX_SIZE + 1);
    EXPECT_EQ(linked_list.Find(100), true);
    EXPECT_EQ(linked_list.RFind(100), true);
    check_elements(linked_list, vec, true);


    // PopBack
    linked_list.PopBack();
    EXPECT_EQ(linked_list.size(), MAX_SIZE);
    EXPECT_EQ(linked_list.Find(100), false);
    EXPECT_EQ(linked_list.RFind(100), false);
    check_elements(linked_list, vec, true);


    // PushFront
    linked_list.PusFront(100);
    EXPECT_EQ(linked_list.Find(100), true);
    EXPECT_EQ(linked_list.RFind(100), true);
    EXPECT_EQ(linked_list.size(), MAX_SIZE + 1);
    check_elements(linked_list, vec, true);


    // PopFront
    linked_list.PopFront();
    EXPECT_EQ(linked_list.Find(100), false);
    EXPECT_EQ(linked_list.RFind(100), false);
    EXPECT_EQ(linked_list.size(), MAX_SIZE);
    check_elements(linked_list, vec, true);

    // Remove
    linked_list.Remove(0);
    EXPECT_EQ(linked_list.Find(0), false);
    EXPECT_EQ(linked_list.RFind(0), false);
    EXPECT_EQ(linked_list.size(), MAX_SIZE - 1);
    vec.erase(vec.begin());
    check_elements(linked_list, vec, true);


    linked_list.Remove(9);
    EXPECT_EQ(linked_list.Find(9), false);
    EXPECT_EQ(linked_list.RFind(9), false);
    EXPECT_EQ(linked_list.size(), MAX_SIZE - 2);
    vec.erase((vec.begin() + 8));
    check_elements(linked_list, vec, true);

    linked_list.Remove(5);
    EXPECT_EQ(linked_list.Find(5), false);
    EXPECT_EQ(linked_list.RFind(5), false);
    EXPECT_EQ(linked_list.size(), MAX_SIZE - 3);
    vec.erase((vec.begin() + 4));
    check_elements(linked_list, vec, true);

    // Clear
    linked_list.Clear();
    EXPECT_EQ(linked_list.size(), 0);
    check_elements(linked_list, vec, false);

    cout << "test done!" << endl << endl;
    
    return 0;
}