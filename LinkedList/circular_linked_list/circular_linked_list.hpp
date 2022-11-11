#ifndef CIRCULAR_LINKED_LIST_HPP
#define CIRCULAR_LINKED_LIST_HPP
#include <iostream>
#include "Logger.hpp"

using namespace std;

template<typename T>
struct Node {
    T data_;
    Node* next_;

    Node() : next_(nullptr){}
    Node(T t) : data_(t), next_(nullptr) {}
    Node(T t, Node* next) : data_(t), next_(next) {}
};

template<typename T>
class CircularLinkedList {
public:
    CircularLinkedList();
    ~CircularLinkedList();

    unsigned int size() const {
        return size_;
    }

    bool Empty() const {
        return size_ == 0;
    }

    bool IsCircular() const;

    void PushBack(const T& val);
    void PopBack();
    bool Find(const T& val);

    void PusFront(const T& val);
    void PopFront();

    void Remove(const T& val);
    void Clear();

private:
    Node<T>* head_;
    unsigned int size_;
};

template<typename T>
CircularLinkedList<T>::CircularLinkedList() : size_(0) {
    head_ = new Node<T>();
    head_->next_ = head_;

    LOG_INFO("%s, constructor.", __FUNCTION__);
}

template<typename T>
CircularLinkedList<T>::~CircularLinkedList() {
    Node<T>* cur = head_->next_;
        
    while (cur != head_) {
        Node<T>* tmp = cur;
        cur = cur->next_;
        delete tmp;
    }

    delete head_;
    head_ = nullptr;
    size_ = 0;

    LOG_INFO("%s, destructor.", __FUNCTION__);
}

template<typename T>
bool CircularLinkedList<T>::IsCircular() const {
    Node<T>* cur = head_->next_;
    for (unsigned int i = 0; i < size_; i++) 
         cur = cur->next_;
       
    return cur == head_;
}

template<typename T>
void CircularLinkedList<T>::PushBack(const T& val) {
    Node<T>* cur = head_;
    while (cur->next_ != head_)
        cur = cur->next_;
    
    cur->next_ = new Node<T>(val, head_);
    ++size_;

    LOG_INFO("%s, size of list: %u.", __FUNCTION__, size_);
}

template<typename T>
void CircularLinkedList<T>::PopBack() {
    Node<T>* cur = head_;
    Node<T>* prev = head_;

    while (cur->next_ != head_) {
        prev = cur;
        cur = cur->next_;
    }

    prev->next_ = cur->next_;

    if (cur != head_) {
        delete cur;
        --size_;
    }

    LOG_INFO("%s, size of list: %u.", __FUNCTION__, size_);
}

template<typename T>
bool CircularLinkedList<T>::Find(const T& val) {
    Node<T>* cur = head_->next_;
    while (cur != head_) {
        if (cur->data_ == val)
            return true;

        cur = cur->next_;
    }

    return false;
}

template<typename T>
void CircularLinkedList<T>::PusFront(const T& val) {
    head_->next_ = new Node<T>(val, head_->next_);
    ++size_;

    LOG_INFO("%s, size of list: %u.", __FUNCTION__, size_);
}

template<typename T>
void CircularLinkedList<T>::PopFront() {
    if (head_->next_ != head_) {
        Node<T>* node = head_->next_;
        head_->next_ = head_->next_->next_;
        delete node;
        --size_;
    }

    LOG_INFO("%s, size of list: %u.", __FUNCTION__, size_);
}

template<typename T>
void CircularLinkedList<T>::Remove(const T& val) {
    Node<T>* prev = head_;

    while (prev->next_ != head_ && prev->next_->data_ != val)
        prev = prev->next_;

    if (prev->next_ != head_) {
        Node<T>* tmp = prev->next_;
        prev->next_ = prev->next_->next_;
        delete tmp;
        --size_;
    }

    LOG_INFO("%s, size of list: %u.", __FUNCTION__, size_);
}

template<typename T>
void CircularLinkedList<T>::Clear() {
    Node<T>* cur = head_->next_;
    while (cur != head_) {
        Node<T>* tmp = cur;
        cur = cur->next_;
        delete tmp;
        --size_;
    }

    cur->next_ = head_;

    LOG_INFO("%s, size of list: %u.", __FUNCTION__, size_);
}

#endif