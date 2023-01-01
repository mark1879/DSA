#ifndef NON_RECURSIVE_BINARY_SEARCH_TREE_HPP
#define NON_RECURSIVE_BINARY_SEARCH_TREE_HPP
#include "binary_search_tree.hpp"
#include <stack>

/**
 * Implemented by Non Recursion
 */
template <typename T>
class NRBSTree : public BSTree<T> 
{
private:
    BSTNode<T>* root_;

public:
    NRBSTree() : root_(nullptr) 
    { }

    ~NRBSTree() 
    { }

    void Insert(const T& key) override 
    {
        BSTNode<T>* new_node = new BSTNode<T>(key);

        if (root_ == nullptr) 
        {
            root_ = new_node;
            return;
        }

        BSTNode<T>* curr = root_;
        BSTNode<T>* parent = nullptr;

        while (curr != nullptr) 
        {
            parent = curr;
            if (key > curr->key_)
                curr = curr->right_;
            else 
                curr = curr->left_;
        }

        if (key > parent->key_)
            parent->right_ = new_node;
        else
            parent->left_ = new_node;
    }

    void Remove(const T& key) override {
        BSTNode<T> *target = root_;
        BSTNode<T> *parent = nullptr;

        while (target != nullptr && target->key_ != key) 
        {
            parent = target;

            if (key > target->key_)
                target = target->right_;
            else
                target = target->left_;
        }

        if (target == nullptr)
            return;

        if (target->left_ != nullptr && target->right_ != nullptr)
        {
            parent = target;
            // Find the largest node in the left subtree
            BSTNode<T>* precursor = target->left_;
            while (precursor->right_ != nullptr)
            {
                parent = precursor;
                precursor = precursor->right_;
            }

            target->key_ = precursor->key_;
            target = precursor;
        }

        BSTNode<T>* child = target->left_ != nullptr ? target->left_ : target->right_;

        if (parent == nullptr)
        {
            root_ = child;
        }
        else
        {
            if (parent->left_ == target)
                parent->left_ = child;
            else
                parent->right_ = child;
        }

        delete target;
    }

    bool Query(const T& key) override {
        BSTNode<T>* target = root_;

        while (target != nullptr && target->key_ != key)
        {
            if (key > target->key_)
                target = target->right_;
            else
                target = target->left_;
        }

        return target != nullptr;
    }

    void PreOrder(std::vector<T>& keys) override 
    {
        if (root_ == nullptr)
            return;

        std::stack<BSTNode<T>*> s;
        BSTNode<T>* curr = root_;

        while (!s.empty() || curr != nullptr) 
        {
            if (curr != nullptr) 
            {
                keys.push_back(curr->key_);
                s.push(curr);
                curr = curr->left_;
            }
            else 
            {
                BSTNode<T>* top = s.top();
                curr = top->right_;
                s.pop();
            }
        }
    }

    void InOrder(std::vector<T>& keys) override 
    {
        if (root_ == nullptr)
            return;

        std::stack<BSTNode<T>*> s;
        BSTNode<T>* curr = root_;

        while (!s.empty() || curr != nullptr) 
        {
            if (curr != nullptr) 
            {
                s.push(curr);
                curr = curr->left_;
            }
            else 
            {
                BSTNode<T>* top = s.top();
                keys.push_back(top->key_);
                curr = top->right_;
                s.pop();
            }
        }
    }

    void PostOrder(std::vector<T>& keys) override 
    {
        if (root_ == nullptr)
            return;

        std::stack<BSTNode<T>*> s;
        BSTNode<T>* curr = root_;

        while (!s.empty() || curr != nullptr) 
        {
            if (curr != nullptr) 
            {
                s.push(curr);
                curr = curr->left_;
            }
            else 
            {
                BSTNode<T>* top = s.top();
                if (top->right_ == nullptr) 
                {
                    keys.push_back(top->key_);
                    s.pop();
                }
                else
                {
                    curr = top->right_;
                    top->right_ = nullptr;
                }
            }
        }
    }
};

#endif