#ifndef MIN_HEAP_HPP
#define MIN_HEAP_HPP
#include <iostream>
#include "priority_queue.hpp"

template<typename T, typename Comp=std::less<T>>
class MinHeap : public PriorityQueue<T>
{
public:
    MinHeap(Comp comp = Comp()) 
        : heap_size_(0)
        , comp_(comp)
    {
    }

    ~MinHeap()
    {
    }

    bool Empty() const override
    {
        return heap_size_ == 0;
    }

    int Size() const override
    {
        return heap_size_;
    }

    bool Top(T& top_elem) const override
    {
        if (Empty())
            return false;

        top_elem = heap_[kTop];

        return true;
    }

    bool Push(const T& elem) override
    {
        heap_.push_back(elem);
        heap_size_++;

        ShiftUp(heap_size_ - 1);

        return true;
    }
    
    bool Pop() override
    {
        if (Empty())
            return false;

        heap_[kTop] = heap_[heap_size_ - 1];
        heap_size_--;

        ShiftDown(heap_size_ - 1);
        
        return true;
    }

private:
    void ShiftUp(int adjusted_pos)
    {
        while (adjusted_pos > kTop)
        {
            int parent = (adjusted_pos - 1) / 2;
            if (comp_(heap_[adjusted_pos], heap_[parent]))
                std::swap(heap_[adjusted_pos], heap_[parent]);

            adjusted_pos = parent;
        }
    }

    int GetAdjustedPos(int target_pos, int last_pos)
    {
        int left_child = target_pos * 2 + 1;
        int right_child = target_pos * 2 + 2;

        if (right_child <= last_pos)
        {
            int smaller = comp_(heap_[left_child], heap_[right_child]) ? left_child : right_child;

            if (comp_(heap_[smaller], heap_[target_pos]))
                return smaller;
        }
        else if (left_child <= last_pos)
        {
            if (comp_(heap_[left_child], heap_[target_pos]))
                return left_child;
        }

        return target_pos;
    }

    void ShiftDown(int last_pos)
    {
        int target_pos = kTop;

        while (target_pos < last_pos)
        {
            int adjusted_pos = GetAdjustedPos(target_pos, last_pos);

            if (adjusted_pos != target_pos)
            {
                std::swap(heap_[adjusted_pos], heap_[target_pos]);
                target_pos = adjusted_pos;
            }
            else
            {
                break;
            }
        }
    }

private:
    int heap_size_;
    std::vector<T> heap_;
    const int kTop = 0;
    Comp comp_;
};

#endif