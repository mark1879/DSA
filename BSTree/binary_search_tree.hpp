#ifndef BINARY_SEARCH_TREE_HPP
#define BINARY_SEARCH_TREE_HPP
#include <functional>

template <typename T>
class BSTNode{
public:
    T key_;
    BSTNode *parent_;
    BSTNode *left_;
    BSTNode *right_;
    
    BSTNode(T key) 
        : key_(key)
        , left_(nullptr)
        , right_(nullptr)
        { }

    BSTNode(T key, BSTNode* left, BSTNode* right)
        : key_(key)
        , left_(left)
        , right_(right) 
        { }
};

template <typename T>
class BSTree {
public:
    BSTree()  { }
    virtual ~BSTree() { }

    virtual void Insert(const T& key) = 0;
    virtual void Remove(const T& key) = 0;
    virtual bool Query(const T& key) = 0;

    virtual void PreOrder(std::vector<T>& keys) = 0;
    virtual void InOrder(std::vector<T>& keys) = 0;
    virtual void PostOrder(std::vector<T>& keys) = 0;
    virtual void LevelOrder(std::vector<T>& keys) = 0;

    virtual unsigned int Height() = 0;
};

#endif