#ifndef PRIORITY_QUEUE_HPP
#define PRIORITY_QUEUE_HPP

#include <vector>

template<typename T>
class PriorityQueue
{
public:
    virtual ~PriorityQueue() {}
    virtual bool Empty() const = 0;
    virtual int Size() const = 0;
    virtual bool Top(T&) const = 0;
    virtual bool Push(const T&) = 0;  //从顶向下调整
    virtual bool Pop() = 0;
};

#endif