#ifndef ARRAY_HPP
#define ARRAY_HPP

#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <string.h>

template <class T>
class Array {
public:
    Array(int capacity = 10) : size_(0), capacity_(capacity) {
        arr_ = new T[capacity_];
    } 

    ~Array() {
        delete[] arr_;
        arr_ = nullptr;
    }

    void push_back(T val) {
        if (size_ == capacity_)
            expand(2 * capacity_);

        arr_[size_++] = val;
    }

    void pop_back() {
        if (size_ == 0)
            return;
        
        size_--;
    }

    void insert(int pos, T val) {
        if (pos < 0 || pos > size_) 
            return;

        if (size_ == capacity_)
            expand(2 * capacity_);

        for (int i = size_; i > pos; i--)
            arr_[i] = arr_[i - 1];

        arr_[pos] = val;
        size_++;
    }

    void erase(int pos) {
        if (pos < 0 || pos >= size_)
            return;

        for (int i = pos; i < size_ - 1; i++)
            arr_[i] = arr_[i + 1];

        size_--;
    }

    bool get(int pos, T& val) {
        if (pos < 0 || pos >= size_)
            return false;

        val = arr_[pos];

        return true;
    }

    int size() const {
        return size_;
    }

    int capacity() const {
        return capacity_;
    }

private:
    void expand(int new_capacity) {
        T* p = new T[new_capacity];
        memcpy(p, arr_, sizeof(T) * capacity_);

        delete[] arr_;
        arr_ = p;
        capacity_ = new_capacity;
    }

private:
    T *arr_;
    int size_;
    int capacity_;
};

#endif
