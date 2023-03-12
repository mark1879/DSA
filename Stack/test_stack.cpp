#include "stack.hpp"
#include "stack_by_linked_list.hpp"
#include <iostream>
#include <gtest/gtest.h>

void TestCase(Stack<int>*& stack)
{
    EXPECT_EQ(stack->Empty(), true);
    EXPECT_EQ(stack->Size(), 0);

    try 
    {
        const int top = stack->Top();
    }
    catch (const char* msg) 
    {
        std::cerr << msg << std::endl;
    }

    for (int i = 0; i < 100; i++)
    {
        stack->Push(i);
        EXPECT_EQ(stack->Empty(), false);
        EXPECT_EQ(stack->Size(), i + 1);
    }

    for (int i = 99; i >= 0; i--)
    {
        EXPECT_EQ(stack->Empty(), false);
        EXPECT_EQ(stack->Top(), i);
        stack->Pop();
        EXPECT_EQ(stack->Size(), i);
    }

    EXPECT_EQ(stack->Empty(), true);
    EXPECT_EQ(stack->Size(), 0);
}


class Test
{
public:
    Test(std::string name = "head")
        : name_(name)
    {
        std::cout << "Test(), name: " << name_ << std::endl;
    }

    ~Test()
    {
        std::cout << "~Test(), name: " << name_ << std::endl;
    }

    Test(const Test& obj)
    {
        this->name_ = obj.name_;
        std::cout << "Test(const Test& obj), name:" << name_ << std::endl;
    }

    Test& operator=(const Test& obj)
    {
        this->name_ = obj.name_;
        std::cout << "Test& operator=(const Test& obj), name:" << name_  << std::endl;

        return *this;
    }

private:
    std::string name_;
};

// Tests whether the object type can be destructed
void TestObjectDestructed()
{
    Stack<Test>* stack = new StackByLinkedList<Test>();

    Test t("t1");
    stack->Push(t);
    stack->Pop();

    delete stack;

    getchar();
}

int main()
{
    std::cout << "test_stack..." << std::endl;

    Stack<int>* stack_by_linked_list = new StackByLinkedList<int>();
    TestCase(stack_by_linked_list);
    
    delete stack_by_linked_list;

    std::cout << "test done!" << std::endl << std::endl;

    return 0;
}