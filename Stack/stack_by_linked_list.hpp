#ifndef LINKED_STACK_HPP
#define LINKED_STACK_HPP
#include "stack.hpp"

template<typename T>
struct StackNode
{
public:
    T val_;
    StackNode *next_;

public:
    StackNode()
    {}

    StackNode(const T& val, StackNode* next)
        : val_(val)
        , next_(next)
    {}
};

template<typename T>
class StackByLinkedList : public Stack<T>
{
public:
    StackByLinkedList() : size_(0)
    {
        head_ = new StackNode<T>();
    }

    ~StackByLinkedList()
    {
        StackNode<T>* iter = head_->next_;
        while (iter != nullptr)
        {
            StackNode<T>* temp = iter;
            iter = iter->next_;
            delete temp;
        }

        delete head_;
        head_ = nullptr;
    }

    bool Empty() const override
    {
        return size_ == 0;
    }

    size_t Size() const override
    {
        return size_;
    }

    bool Push(const T& val) override
    {
        if (size_ > kMaxSize)
            return false;

        StackNode<T>* new_node = new StackNode<T>(val, head_->next_);
        head_->next_ = new_node;
        ++size_;

        return true;
    }

    bool Top(T& val) const override
    {
        if (size_ == 0)
            return false;

        val = head_->next_->val_;
        
        return true;
    }

    void Pop() override
    {
        if (size_ == 0)
            return;

        StackNode<T>* top = head_->next_;
        head_->next_ = top->next_;
        delete top;
        --size_;
    }

private:
    size_t size_;
    StackNode<T>* head_;
    const size_t kMaxSize = 10000;
};



#endif