#ifndef DOUBLY_CIRCULAR_LINKED_LIST
#define DOUBLY_CIRCULAR_LINKED_LIST
#include <iostream>
#include "logger.hpp"

using namespace std;

template<typename T>
struct Node {
    T data_;
    Node* next_;
    Node* prev_;

    Node() : next_(nullptr), prev_(nullptr) {}
    Node(T data) : data_(data), next_(nullptr), prev_(nullptr) {}
};

template<typename T>
class DoublyCircularLinkedList {
public:
    DoublyCircularLinkedList();
    ~DoublyCircularLinkedList();

     unsigned int size() const {
        return size_;
    }

    bool Empty() const {
        return size_ == 0;
    }

    bool IsDoublyCircular() const;

    void PushBack(const T& val);
    void PopBack();
    bool Find(const T& val);
    bool RFind(const T& val);

    void PusFront(const T& val);
    void PopFront();

    bool Insert(const unsigned int pos, const T& val);
    void Remove(const T& val);
    void Clear();

private:
    unsigned size_;
    Node<T>* head_;
    Node<T>* tail_;
};

template<typename T>
DoublyCircularLinkedList<T>:: DoublyCircularLinkedList() : size_(0) {
    head_ = new Node<T>();
    tail_ = new Node<T>();

    head_->next_ = tail_;
    head_->prev_ = tail_;

    tail_->prev_ = head_;
    tail_->next_ = head_;

    LOG_INFO("%s, constructor.", __FUNCTION__);
}

template<typename T>
DoublyCircularLinkedList<T>::~DoublyCircularLinkedList() {
    Node<T>* node = head_->next_;
    while (node != tail_) {
        Node<T>* tmp = node;
        node = node->next_;
        delete tmp;
    }

    delete head_;
    delete tail_;
    size_ = 0;

    LOG_INFO("%s, destructor.", __FUNCTION__);
}

template<typename T>
bool DoublyCircularLinkedList<T>::IsDoublyCircular() const {
    Node<T>* next = head_->next_;
    for (unsigned int i = 0; i < size_; i++)
        next = next->next_;

    Node<T>* prev = tail_->prev_;
    for (unsigned int i = 0; i < size_; i++)
        prev = prev->prev_;

    return (next == tail_) && (prev == head_);
}

template<typename T>
void DoublyCircularLinkedList<T>::PushBack(const T& val) {
    Node<T>* node = new Node<T>(val);

    tail_->prev_->next_ = node;
    node->prev_ = tail_->prev_;
    node->next_ = tail_;
    tail_->prev_ = node;

    ++size_;

    LOG_INFO("%s, size of list: %u.", __FUNCTION__, size_);
}

template<typename T>
void DoublyCircularLinkedList<T>::PopBack() {
    if (Empty()) {
        LOG_WARNING("%s, the list is empty!", __FUNCTION__);
        return;
    } 

    Node<T>* del = tail_->prev_;
    del->prev_->next_ = tail_;
    tail_->prev_ = del->prev_;

    delete del;
    --size_;

    LOG_INFO("%s, size of list: %u.", __FUNCTION__, size_);
}

template<typename T>
bool DoublyCircularLinkedList<T>::Find(const T& val) {
    if (Empty()) {
        LOG_WARNING("%s, the list is empty!", __FUNCTION__);
        return false;
    } 

    Node<T>* node = head_->next_;
    while (node != tail_) {
        if (node->data_ == val)
            return true;

        node = node->next_;
    }

    return false;
}

template<typename T>
bool DoublyCircularLinkedList<T>::RFind(const T& val) {
    if (Empty()) {
        LOG_WARNING("%s, the list is empty!", __FUNCTION__);
        return false;
    } 

    Node<T>* node = tail_->prev_;
    while (node != head_) {
        if (node->data_ == val)
            return true;
        
        node = node->prev_;
    }

    return false;
}

template<typename T>
void DoublyCircularLinkedList<T>::PusFront(const T& val) {
    Node<T>* node = new Node<T>(val);
    node->next_ = head_->next_;
    head_->next_->prev_ = node;
    node->prev_ = head_;
    head_->next_ = node;
    ++size_;

    LOG_INFO("%s, size of list: %u.", __FUNCTION__, size_);
}

template<typename T>
void DoublyCircularLinkedList<T>::PopFront() {
    if (Empty()) {
        LOG_WARNING("%s, the list is empty!", __FUNCTION__);
        return;
    }

    Node<T>* del = head_->next_;
    head_->next_ = del->next_;
    del->next_->prev_ = head_;
    --size_;

    LOG_INFO("%s, size of list: %u.", __FUNCTION__, size_);
}

template<typename T>
bool DoublyCircularLinkedList<T>::Insert(const unsigned int pos, const T& val) {
    if (pos > size_) {
        LOG_WARNING("%s, pos(%u) is valid, size(%u)", __FUNCTION__, pos, size_);
        return false;
    }

    unsigned int index = 0;
    Node<T>* cur = head_->next_;
    while (index < pos) {
        cur = cur->next_;
        ++index;
    }
        
    Node<T>* node = new Node<T>(val);
    cur->prev_->next_ = node;
    node->prev_ = cur->prev_;
    node->next_ = cur;
    cur->prev_ = node;
    ++size_;

    LOG_INFO("%s, size of list: %u.", __FUNCTION__, size_);

    return true;
}

template<typename T>
void DoublyCircularLinkedList<T>::Remove(const T& val) {
    if (Empty()) {
        LOG_WARNING("%s, the list is empty!", __FUNCTION__);
        return;
    }

    Node<T>* cur = head_->next_;
    while (cur != tail_ && cur->data_ != val)
        cur = cur->next_;

    if (cur != tail_) {
        Node<T>* del = cur;
        cur->prev_->next_ = cur->next_;
        cur->next_->prev_ = cur->prev_;
        --size_;
        delete del;
    }


    LOG_INFO("%s, size of list: %u.", __FUNCTION__, size_);
}

template<typename T>
void DoublyCircularLinkedList<T>::Clear() {
    Node<T>* cur = head_->next_;
    while (cur != tail_) {
        Node<T>* tmp = cur;
        cur = cur->next_;
        delete tmp;
    }

    head_->next_ = tail_;
    head_->prev_ = tail_;

    tail_->prev_ = head_;
    tail_->next_ = head_;

    size_ = 0;

    LOG_INFO("%s, size of list: %u.", __FUNCTION__, size_);
}



#endif