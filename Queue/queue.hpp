#ifndef QUEUE_HPP
#define QUEUE_HPP
#include <iostream>

template<typename T>
class Queue 
{
public:
    virtual ~Queue() {}
    virtual bool Empty() const = 0;
    virtual size_t Size() const = 0;
    virtual void Push(const T&) = 0;
    virtual void Pop() = 0;
    virtual T Front() const = 0;
    virtual T Back() const = 0;
};


#endif
