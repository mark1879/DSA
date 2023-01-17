#ifndef AVL_TREE_HPP
#define AVL_TREE_HPP
#include <iostream>
#include <vector>

template<typename T>
struct AVLTNode {
public:
    AVLTNode(T key)
        : key_(key)
        , left_(nullptr)
        , right_(nullptr)
        , height_(1)
    { }

public:
    T key_;
    AVLTNode* left_;
    AVLTNode* right_;
    int height_;
};

template<typename T>
class AVLTree {
public:
    AVLTree() { }
    virtual ~AVLTree() { }

    virtual void Insert(const T& key) = 0;
    virtual void Remove(const T& key) = 0;
    virtual bool Query(const T& key) const = 0;

    virtual bool IsBalance() const = 0;

    virtual void InOrder(std::vector<T>& keys) const = 0;
};

#endif