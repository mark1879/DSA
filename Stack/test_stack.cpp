#include "stack.hpp"
#include "linked_stack.hpp"
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

    Stack<int>* linked_stack = new LinkedStack<int>();
    TestCase(linked_stack);

    std::cout << "test done!" << std::endl;

    return 0;
}