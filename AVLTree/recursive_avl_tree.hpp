#ifndef RECURSIVE_AVL_TREE_HPP
#define RECURSIVE_AVL_TREE_HPP
#include <algorithm>
#include <cmath>
#include "avl_tree.hpp"

template<typename T>
class RAVLTree : public AVLTree<T> {
public:
    RAVLTree() : root_(nullptr) 
    { }

    ~RAVLTree()
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

    bool Query(const T& key) const override
    {
        return Query(root_, key) != nullptr;
    }

    bool IsBalance() const override
    {
        return IsBalance(root_);
    }

    void InOrder(std::vector<T>& keys) const override
    {
        InOrder(root_, keys);
    }

private:
    int Height(const AVLTNode<T>* node) const 
    {
        return node == nullptr ? 0 : node->height_;
    }

    bool IsBalance(const AVLTNode<T>* node) const 
    {
        if (node == nullptr)
            return true;
        
        return abs(Height(node->left_) - Height(node->right_)) <= 1
                && IsBalance(node->left_) && IsBalance(node->right_);
    }

    void InOrder(const AVLTNode<T>* node, std::vector<T>& keys) const 
    {
        if (node != nullptr) 
        {
            InOrder(node->left_, keys);
            keys.push_back(node->key_);
            InOrder(node->right_, keys);
        }
    }

    AVLTNode<T>* Query(AVLTNode<T>* node, const T& key) const 
    {
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

    void Destroy(AVLTNode<T>* node) 
    {
        if (node == nullptr)
            return;
    
        if (node->left_ != nullptr)
            Destroy(node->left_);

        if (node->right_ != nullptr)
            Destroy(node->right_);
    
        delete node;
    }

    /**
     *      10
     *     /
     *    6
     *   /
     *  3
     */
    AVLTNode<T>* RightRotate(AVLTNode<T>* node) 
    {
        AVLTNode<T>* child = node->left_;
        node->left_ = child->right_;
        child->right_ = node;

        child->height_ = std::max(Height(child->left_), Height(child->right_)) + 1;
        node->height_ = std::max(Height(node->left_), Height(node->right_)) + 1;

        return child;
    }

    /**
     *  10
     *    \ 
     *    15
     *      \
     *       20
     */
    AVLTNode<T>* LeftRotate(AVLTNode<T>* node) 
    {
        AVLTNode<T>* child = node->right_;
        node->right_ = child->left_;
        child->left_ = node;

        child->height_ = std::max(Height(child->left_), Height(child->right_)) + 1;
        node->height_ = std::max(Height(node->left_), Height(node->right_)) + 1;

        return child;
    }

     /**
     *     10
     *    /
     *   6
     *    \
     *     8
     */
    AVLTNode<T>* LeftBalance(AVLTNode<T>* node) 
    {
        node->left_ = LeftRotate(node->left_);
        return RightRotate(node);
    }

    /**
     *  10
     *   \
     *    15
     *    /
     *  12
     */
    AVLTNode<T>* RightBalance(AVLTNode<T>* node) 
    {
        node->right_ = RightRotate(node->right_);
        return LeftRotate(node);
    }

    void Adjust(AVLTNode<T>*& node)
    {
        if (Height(node->left_) - Height(node->right_) > 1)
        {
            if (Height(node->left_->left_) >= Height(node->left_->right_))
                node = RightRotate(node);
            else
                node = LeftBalance(node);
        }
        else if (Height(node->right_) - Height(node->left_) > 1)
        {
            if (Height(node->right_->right_) >= Height(node->right_->left_))
                node = LeftRotate(node);
            else
                node = RightBalance(node);
        }
    }

    AVLTNode<T>* Insert(AVLTNode<T>* node, const T& key) 
    {
        if (node == nullptr)
            return new AVLTNode<T>(key);

        if (key < node->key_)
        {
            node->left_ = Insert(node->left_, key);
            Adjust(node);
        }
        else if (key > node->key_)
        {
            node->right_ = Insert(node->right_, key);
            Adjust(node);
        }

        node->height_ = std::max(Height(node->left_), Height(node->right_)) + 1;

        return node;
    }

    AVLTNode<T>* Remove(AVLTNode<T>* node, const T& key) {
        if (node == nullptr)
            return nullptr;

        if (key < node->key_) 
        {
            node->left_ = Remove(node->left_, key);
            Adjust(node);
        } 
        else if (key > node->key_) 
        {
            node->right_ = Remove(node->right_, key);
            Adjust(node);
        } 
        else 
        {
            if (node->left_ != nullptr && node->right_ != nullptr) 
            {
                if (Height(node->left_) >= Height(node->right_))
                {
                    AVLTNode<T>* pre = node->left_;
                    while (pre->right_ != nullptr)
                        pre = pre->right_;

                    node->key_ = pre->key_;
                    node->left_ = Remove(node->left_, pre->key_);
                }
                else
                {
                    AVLTNode<T>* post = node->right_;
                    while (post->left_ != nullptr)
                        post = post->left_;

                    node->key_ = post->key_;
                    node->right_ = Remove(node->right_, post->key_);
                }
            } 
            else if (node->left_ != nullptr || node->right_ != nullptr) 
            {
                AVLTNode<T>* tmp = node->left_ != nullptr ? node->left_ : node->right_;
                delete node;
                return tmp;
            } 
            else 
            {
                return nullptr;
            }
        }

        node->height_ = std::max(Height(node->left_), Height(node->right_)) + 1;

        return node;
    }

private:
    AVLTNode<T>* root_;
};

#endif