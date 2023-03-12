#include "queue.hpp"
#include "queue_by_linked_list.hpp"
#include <iostream>
#include <gtest/gtest.h>

void TestCase(Queue<int>* queue)
{
    EXPECT_EQ(queue->Size(), 0);
    EXPECT_EQ(queue->Empty(), true);

    try 
    {
        const int front = queue->Front();
    }
    catch (const char* msg) 
    {
        std::cerr << msg << std::endl;
    }

    try 
    {
        const int back = queue->Back();
    }
    catch (const char* msg) 
    {
        std::cerr << msg << std::endl;
    }

    for (int i = 0; i < 100; i++)
    {
        queue->Push(i);

        EXPECT_EQ(queue->Size(), i + 1);
        EXPECT_EQ(queue->Empty(), false);

        const int front = queue->Front();
        EXPECT_EQ(front, 0);

        const int back = queue->Back();
        EXPECT_EQ(back, i);
    }

    for (int i = 0; i < 100; i++)
    {
        EXPECT_EQ(queue->Empty(), false);

        const int front = queue->Front();
        EXPECT_EQ(front, i);

        const int back = queue->Back();
        EXPECT_EQ(back, 99);

        queue->Pop();
        EXPECT_EQ(queue->Size(), (100 - i - 1));
    }

    EXPECT_EQ(queue->Size(), 0);
    EXPECT_EQ(queue->Empty(), true);

}

int main()
{
    std::cout << "test_queue..." << std::endl;

    Queue<int>* queue_by_linked_list = new QueueByLinkedList<int>();
    TestCase(queue_by_linked_list);

    delete queue_by_linked_list;

    std::cout << "test done!" << std::endl << std::endl;

    return 0;
}