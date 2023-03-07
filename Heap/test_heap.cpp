#include "priority_queue.hpp"
#include "min_heap.hpp"
#include "max_heap.hpp"
#include <iostream>
#include <gtest/gtest.h>

void TestCase(PriorityQueue<int>* heap, std::vector<int> data, std::vector<int> ans)
{
    for (auto it : data)
        heap->Push(it);

    for (auto it : ans)
    {
        int top;
        EXPECT_EQ(heap->Top(top), true);
        EXPECT_EQ(top, it);
        heap->Pop();
    }
}

int main()
{
    std::cout << "test_heap..." << std::endl;

    std::vector<int> data = {9, 8, 8, 7, 10, 3, 4, 9, 1, 1};

    PriorityQueue<int>* min_heap = new MinHeap<int>();
    TestCase(min_heap, data, {1, 1, 3, 4, 7, 8, 8, 9, 9, 10});

    PriorityQueue<int>* max_heap = new MaxHeap<int>();
    TestCase(max_heap, data, {10, 9, 9, 8, 8, 7, 4, 3, 1, 1});

    delete(min_heap);
    delete(max_heap);

    std::cout << "test done!" << std::endl << std::endl;

    return 0;
}