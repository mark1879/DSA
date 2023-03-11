#ifndef STACK_HPP
#define STACK_HPP
#include <iostream>

template<typename T>
class Stack
{
public:
    virtual ~Stack() {}
    virtual bool Empty() const = 0;
    virtual size_t Size() const = 0;
    virtual void Push(const T&) = 0;
    virtual T Top() const = 0;
    virtual void Pop() = 0;
};

#endif