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
class LinkedList {
public:
    LinkedList();
    ~LinkedList();

    unsigned int size() const {
        return size_;
    }

    bool Empty() const {
        return size_ == 0;
    }

    void PushBack(const T& value);
    void PopBack();
    bool Find(const T& value);

private:
    Node<T>* head_;
    unsigned int size_;
};

template<typename T>
LinkedList<T>::LinkedList() : size_(0) {
    head_ = new Node<T>();

    LOG_INFO("%s, constructor.", __FUNCTION__);
}

template<typename T>
LinkedList<T>::~LinkedList() {
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
void LinkedList<T>::PushBack(const T& value) {
    Node<T>* curr = head_;

    while (curr->next_ != nullptr)
        curr = curr->next_;
    
    curr->next_ = new Node<T>(value);
    ++size_;
    
    LOG_INFO("%s, size of list: %u.", __FUNCTION__, size_);
}

template<typename T>
void LinkedList<T>::PopBack() {
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
bool LinkedList<T>::Find(const T& value) {
    Node<T>* node = head_->next_;

    while (node != nullptr) {
        if (node->data_ == value)
            return true;
        
        node = node->next_;
    }

    return false;
}


#endif