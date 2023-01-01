#ifndef RECURSIVE_BINARY_SEARCH_TREE_HPP
#define RECURSIVE_BINARY_SEARCH_TREE_HPP
#include "binary_search_tree.hpp"
#include <functional>
#include <vector>
#include <iostream>
#include "Logger.hpp"

/**
 * Implemented by Recursion
 */
template <typename T>
class RBSTree : public BSTree<T> 
{
private:
    BSTNode<T>* root_;

public:
    RBSTree() 
        : root_(nullptr)
    { }

    ~RBSTree() 
    {
        Destroy(root_);
        root_ = nullptr;
    }

    void Insert(const T& key) override 
    {
        root_ = Insert(root_, key);
    }

    void Remove(const T& key) override 
    {
        root_ = Remove(root_, key);
    }

    bool Query(const T& key) override 
    {
        return Query(root_, key) != nullptr;
    }

    void PreOrder(std::vector<T>& keys) override 
    {
        PreOrder(root_, keys);
    }

    void InOrder(std::vector<T>& keys) override 
    {
        InOrder(root_, keys);
    }

    void PostOrder(std::vector<T>& keys) override 
    {
        PostOrder(root_, keys);
    }

private:
    BSTNode<T>* Insert(BSTNode<T>* node, const T& key) 
    {
        if (node == nullptr) 
            return new BSTNode<T>(key);

        if (key > node->key_) 
        {
            node->right_ = Insert(node->right_, key);
        }
        else
        {
            node->left_ = Insert(node->left_, key);
        }

        return node;
    }

    BSTNode<T>* Remove(BSTNode<T>* node, const T& key) 
    {
        if (node == nullptr) 
            return nullptr;
            
        if (key > node->key_) 
        {
            node->right_ = Remove(node->right_, key);
        }
        else if (key < node->key_) 
        {
            node->left_ = Remove(node->left_, key);
        }
        else    
        {   // got the node
            if (node->left_ != nullptr && node->right_ != nullptr) 
            {
                // Find the largest node in the left subtree
                BSTNode<T>* precursor = node->left_;
                while (precursor->right_ != nullptr)
                {
                    precursor = precursor->right_;
                }
                node->key_ = precursor->key_;
                node->left_ = Remove(node->left_, precursor->key_);
            } 
            else if(node->left_ != nullptr || node->right_ != nullptr) 
            {
                BSTNode<T>* tmp = node->left_ != nullptr ? node->left_ : node->right_;
                delete node;
                return tmp;
            } 
            else 
            {
                delete node;
                return nullptr;
            }
        }

        return node;
    }

    BSTNode<T>* Query(BSTNode<T>* node, const T& key) {
        if (node == nullptr)
            return nullptr;

        if (key > node->key_) 
        {
            return Query(node->right_, key);
        }
        else if (key < node->key_)
        {
            return Query(node->left_, key);
        }

        return node;
    }

    void PreOrder(const BSTNode<T>* node, std::vector<T>& keys) {
        if (node != nullptr) {
            keys.push_back(node->key_);
            PreOrder(node->left_, keys);
            PreOrder(node->right_, keys);
        }
    }

    void InOrder(const BSTNode<T>* node, std::vector<T>& keys) {
        if (node != nullptr) {
            InOrder(node->left_, keys);
            keys.push_back(node->key_);
            InOrder(node->right_, keys);
        }
    }

    void PostOrder(const BSTNode<T>* node, std::vector<T>& keys) {
        if (node != nullptr) {
            PostOrder(node->left_, keys);
            PostOrder(node->right_, keys);
            keys.push_back(node->key_);
        }
    }

    void Destroy(BSTNode<T>* node) {
        if (node == nullptr)
            return;
    
        if (node->left_ != nullptr)
            Destroy(node->left_);

        if (node->right_ != nullptr)
            Destroy(node->right_);
    
        delete node;
    }
};


#endif