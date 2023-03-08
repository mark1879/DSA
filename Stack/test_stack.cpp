#include "stack.hpp"
#include "stack_by_linked_list.hpp"
#include <iostream>
#include <gtest/gtest.h>

void TestCase(Stack<int>*& stack)
{
    EXPECT_EQ(stack->Empty(), true);
    int top;
    EXPECT_EQ(stack->Top(top), false);

    for (int i = 0; i < 100; i++)
    {
        stack->Push(i);
        EXPECT_EQ(stack->Empty(), false);
        EXPECT_EQ(stack->Size(), i + 1);
    }

    for (int i = 99; i >= 0; i--)
    {
        EXPECT_EQ(stack->Top(top), true);
        EXPECT_EQ(top, i);
        stack->Pop();
        EXPECT_EQ(stack->Size(), i);
    }

    EXPECT_EQ(stack->Empty(), true);
    EXPECT_EQ(stack->Top(top), false);
}

int main()
{
    std::cout << "test_stack..." << std::endl;

    Stack<int>* stack_by_linked_list = new StackByLinkedList<int>();
    TestCase(stack_by_linked_list);

    std::cout << "test done!" << std::endl;

    return 0;
}