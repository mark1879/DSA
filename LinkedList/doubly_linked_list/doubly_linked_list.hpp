#ifndef DOUBLY_LINKED_LIST_HPP
#define DOUBLY_LINKED_LIST_HPP
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
class DoublyLinkedList {
public:
    DoublyLinkedList();
    ~DoublyLinkedList();

     unsigned int size() const {
        return size_;
    }

    bool Empty() const {
        return size_ == 0;
    }

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
DoublyLinkedList<T>:: DoublyLinkedList() : size_(0) {
    head_ = new Node<T>();
    tail_ = new Node<T>();

    head_->next_ = tail_;
    tail_->prev_ = head_;

    LOG_INFO("%s, constructor.", __FUNCTION__);
}

template<typename T>
DoublyLinkedList<T>::~DoublyLinkedList() {
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
void DoublyLinkedList<T>::PushBack(const T& val) {
    Node<T>* node = new Node<T>(val);

    tail_->prev_->next_ = node;
    node->prev_ = tail_->prev_;
    node->next_ = tail_;
    tail_->prev_ = node;

    ++size_;

    LOG_INFO("%s, size of list: %u.", __FUNCTION__, size_);
}

template<typename T>
void DoublyLinkedList<T>::PopBack() {
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
bool DoublyLinkedList<T>::Find(const T& val) {
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
bool DoublyLinkedList<T>::RFind(const T& val) {
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
void DoublyLinkedList<T>::PusFront(const T& val) {
    Node<T>* node = new Node<T>(val);
    node->next_ = head_->next_;
    head_->next_->prev_ = node;
    node->prev_ = head_;
    head_->next_ = node;
    ++size_;

    LOG_INFO("%s, size of list: %u.", __FUNCTION__, size_);
}

template<typename T>
void DoublyLinkedList<T>::PopFront() {
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
bool DoublyLinkedList<T>::Insert(const unsigned int pos, const T& val) {
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
void DoublyLinkedList<T>::Remove(const T& val) {
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
void DoublyLinkedList<T>::Clear() {
    Node<T>* cur = head_->next_;
    while (cur != tail_) {
        Node<T>* tmp = cur;
        cur = cur->next_;
        delete tmp;
    }

    head_->next_ = tail_;
    tail_->prev_ = head_;
    size_ = 0;

    LOG_INFO("%s, size of list: %u.", __FUNCTION__, size_);
}

#endif