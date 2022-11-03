#ifndef LINKED_LIST_HPP
#define LINKED_LIST_HPP
#include <iostream>
#include "Logger.hpp"

using namespace std;

template <typename T>
struct Node {
    T data_;
    Node* next_;

    Node() : data_(0), next_(nullptr) { }
    Node(T t) : data_(t), next_(nullptr) { }
    Node(T t, Node *next) : data_(t), next_(next){ }
};

template <typename T>
class SinglyLinkedList {
public:
    SinglyLinkedList();
    ~SinglyLinkedList();

    unsigned int size() const {
        return size_;
    }

    bool Empty() const {
        return size_ == 0;
    }

    void PushBack(const T& value);
    void PopBack();
    bool Find(const T& value);

    void PusFront(const T& value);
    void PopFront();

    bool Insert(const unsigned int pos, const T& value);
    void Remove(const T& value);
    void Clear();

private:
    Node<T>* head_;
    unsigned int size_;
};

template<typename T>
SinglyLinkedList<T>::SinglyLinkedList() : size_(0) {
    head_ = new Node<T>();

    LOG_INFO("%s, constructor.", __FUNCTION__);
}

template<typename T>
SinglyLinkedList<T>::~SinglyLinkedList() {
    Node<T>* p = head_->next_;
        
    while (p != nullptr) {
        Node<T>* tmp = p;
        p = p->next_;
        delete tmp;
    }

    delete head_;
    head_ = nullptr;

    LOG_INFO("%s, destructor.", __FUNCTION__);
}

template<typename T>
void SinglyLinkedList<T>::PushBack(const T& value) {
    Node<T>* curr = head_;

    while (curr->next_ != nullptr)
        curr = curr->next_;
    
    curr->next_ = new Node<T>(value);
    ++size_;
    
    LOG_INFO("%s, size of list: %u.", __FUNCTION__, size_);
}

template<typename T>
void SinglyLinkedList<T>::PopBack() {
    Node<T>* curr = head_;
    Node<T>* prev = head_;

    while (curr->next_ != nullptr) {
        prev = curr;
        curr = curr->next_;
    }

    if (curr != head_) {
        prev->next_ = nullptr;
        delete curr;
        --size_;
    }

    LOG_INFO("%s, size of list: %u.", __FUNCTION__, size_);
}

template<typename T>
bool SinglyLinkedList<T>::Find(const T& value) {
    Node<T>* node = head_->next_;

    while (node != nullptr) {
        if (node->data_ == value)
            return true;
        
        node = node->next_;
    }

    return false;
}

template<typename T>
void SinglyLinkedList<T>::PusFront(const T& value) {
    Node<T>* node = new Node<T>(value, head_->next_);
    head_->next_ = node;
    ++size_;

    LOG_INFO("%s, size of list: %u.", __FUNCTION__, size_);
}

template<typename T>
void SinglyLinkedList<T>::PopFront() {
    if (head_->next_ != nullptr) {
        head_->next_ = head_->next_->next_;
        --size_;
    }

    LOG_INFO("%s, size of list: %u.", __FUNCTION__, size_);
}

template<typename T>
bool SinglyLinkedList<T>::Insert(const unsigned int pos, const T& value) {
    LOG_INFO("%s, pos: %u, size of list: %u.", __FUNCTION__, pos, size_);

    if (pos > size_)
        return false;

    unsigned int index = 0;
    Node<T>* prev = head_;

    while (index < pos) {
        index++;
        prev = prev->next_;
    }

    Node<T>* node = new Node<T>(value, prev->next_);
    prev->next_ = node;
    ++size_;

    return true;
}

template<typename T>
void SinglyLinkedList<T>::Remove(const T& value) {
    Node<T>* prev = head_;

    while (prev->next_ != nullptr && prev->next_->data_ != value)
        prev = prev->next_;

    if (prev->next_ != nullptr) {
        Node<T>* tmp = prev->next_;
        prev->next_ = prev->next_->next_;
        delete tmp;
        --size_;
    }

    LOG_INFO("%s, size of list: %u.", __FUNCTION__, size_);
}

template<typename T>
void SinglyLinkedList<T>::Clear() {
    Node<T>* curr = head_;

    while (curr->next_ != nullptr) {
        Node<T>* tmp = curr->next_;
        curr->next_ = curr->next_->next_;
        delete tmp;
    }

    size_ = 0;
    LOG_INFO("%s, size of list: %u.", __FUNCTION__, size_);
}


#endif