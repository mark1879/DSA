#ifndef QUEUE_BY_LINKED_LIST_HPP
#define QUEUE_BY_LINKED_LIST_HPP
#include "queue.hpp"

template<typename T>
struct QueueNode 
{
public:
    T val_;
    QueueNode* next_;
public:
    QueueNode() : next_(nullptr)
    {}

    QueueNode(const T& t, QueueNode* next)
        : val_(t)
        , next_(next)
    {}
};

template<typename T>
class QueueByLinkedList : public Queue<T>
{
public:
    QueueByLinkedList() : size_(0)
    {
        front_ = new QueueNode<T>();
        back_ = front_;
    }

    ~QueueByLinkedList()
    {
        QueueNode<T>* iter = front_->next_;
        while (iter != nullptr)
        {
            QueueNode<T>* tmp = iter;
            iter = iter->next_;
            delete tmp;
        }

        delete front_;
        front_ = back_ = nullptr;
    }

    bool Empty() const override
    {
        return size_ == 0;
    }

    size_t Size() const override
    {
        return size_;
    }

    void Push(const T& val) override
    {
        back_->next_ = new QueueNode<T>(val, nullptr);
        back_ = back_->next_;
        ++size_;
    }

    void Pop() override
    {
        if (size_ == 0)
            return;

        QueueNode<T>* top = front_->next_;
        front_->next_ = top->next_;
        delete top;
        --size_;

        if (size_ == 0)
            back_ = front_;
    }

    T Front() const override
    {
        if (size_ == 0)
            throw("QueueByLinkedList::Front(), queue is empty!");

        return front_->next_->val_;
    }

    T Back() const override
    {
        if (size_ == 0)
            throw("QueueByLinkedList::Front(), queue is empty!");

        return back_->val_;
    }

private:
    size_t size_;
    QueueNode<T>* front_;
    QueueNode<T>* back_;
};

#endif 