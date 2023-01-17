#ifndef NON_RECURSIVE_AVL_TREE_HPP
#define NON_RECURSIVE_AVL_TREE_HPP
#include "avl_tree.hpp"
#include <stack>
#include <queue>

template<typename T>
class NRAVLTree : public AVLTree<T>
{
public:
    NRAVLTree() : root_(nullptr)
    { }

    ~NRAVLTree()
    { 
        if (root_ != nullptr)
        {
            std::queue<AVLTNode<T>*> s;
            s.push(root_);

            while (!s.empty())
            {
                AVLTNode<T>* front = s.front();

                if (front->left_ != nullptr)
                    s.push(front->left_);

                if (front->right_ != nullptr)
                    s.push(front->right_);

                delete front;
                s.pop();
            } 

            root_ = nullptr;
        }
    }

    void Insert(const T& key) override
    {   
        if (root_ == nullptr)
        {
            root_ = new AVLTNode<T>(key);
            return;
        }

        AVLTNode<T>** curr = &root_;
        std::stack<AVLTNode<T>**> s;

        while (*curr != nullptr)
        {
            s.push(curr);

            if (key < (*curr)->key_)
                curr = &((*curr)->left_);
            else if (key > (*curr)->key_)
                curr = &((*curr)->right_);
            else
                return;     // the key has been existed!
        }

        *curr = new AVLTNode<T>(key);

        while (!s.empty())
        {
            AVLTNode<T>** node = s.top();
            s.pop();
            Adjust(*node);
        } 
    }

    void Remove(const T& key) override
    {
         if (root_ == nullptr)
            return;

        AVLTNode<T>** curr = &root_;
        std::stack<AVLTNode<T>**> s;

        while (*curr != nullptr)
        {
            s.push(curr);

            if (key < (*curr)->key_)
            {
                curr = &((*curr)->left_);
            }
            else if (key > (*curr)->key_)
            {
                curr = &((*curr)->right_);
            }
            else
            {
                if ((*curr)->left_ != nullptr && (*curr)->right_ != nullptr)
                {
                    AVLTNode<T>** target = curr;
                    curr = &((*curr)->right_);
                    s.push(curr);

                    while ((*curr)->left_ != nullptr)
                    {
                        curr = &((*curr)->left_);
                        s.push(curr);
                    }

                    (*target)->key_ = (*curr)->key_;
                }

                *curr = ((*curr)->left_ != nullptr) ? (*curr)->left_ : (*curr)->right_;
                delete *(s.top());
                s.pop();

                while (!s.empty())
                {
                    AVLTNode<T>** node = s.top();
                    s.pop();
                    Adjust(*node);
                }
            }
        }
    }

    bool Query(const T& key) const override
    {
        AVLTNode<T>* target = root_;

        while (target != nullptr && target->key_ != key)
        {
            if (key > target->key_)
                target = target->right_;
            else
                target = target->left_;
        }

        return target != nullptr;
    }

    bool IsBalance() const override
    {
        if (root_ == nullptr)
            return true;

        std::stack<AVLTNode<T>*> s;
        AVLTNode<T>* curr = root_;

        bool is_balance = true;

        while (curr != nullptr || !s.empty())
        {
            if (curr != nullptr)
            {
                is_balance &= (abs(Height(curr->left_) - Height(curr->right_)) <= 1);
                s.push(curr);
                curr = curr->left_;
            }
            else
            {
                AVLTNode<T>* top = s.top();
                curr = top->right_;
                s.pop();
            }
        }

        return is_balance;
    }

    void InOrder(std::vector<T>& keys) const override
    {
        if (root_ == nullptr)
            return;

        std::stack<AVLTNode<T>*> s;
        AVLTNode<T>* curr = root_;

        while (curr != nullptr || !s.empty())
        {
            if (curr != nullptr)
            {
                s.push(curr);
                curr = curr->left_;
            }
            else
            {
                AVLTNode<T>* top = s.top();
                keys.push_back(top->key_);
                curr = top->right_;
                s.pop();
            }
        }
    }

private:
    int Height(const AVLTNode<T>* node) const
    {
        return node == nullptr ? 0 : node->height_;
    }

    void Adjust(AVLTNode<T>*& node)
    {
        if (Height(node->left_) - Height(node->right_) > 1)
        {
            if (Height(node->left_->left_) >= Height(node->left_->right_))
                RightRotate(node);
            else
                LeftBalance(node);
        }
        else if (Height(node->right_) - Height(node->left_) > 1)
        {
            if (Height(node->right_->right_) >= Height(node->right_->left_))
                LeftRotate(node);
            else
                RightBalance(node);
        }

        node->height_ = std::max(Height(node->left_), Height(node->right_)) + 1; 
    }

     /**
     *      10
     *     /
     *    6
     *   /
     *  3
     */
    void RightRotate(AVLTNode<T>*& node) 
    {
        AVLTNode<T>* child = node->left_;
        node->left_ = child->right_;
        child->right_ = node;

        child->height_ = std::max(Height(child->left_), Height(child->right_)) + 1;
        node->height_ = std::max(Height(node->left_), Height(node->right_)) + 1;

        node = child;
    }

    /**
     *  10
     *    \ 
     *    15
     *      \
     *       20
     */
    void LeftRotate(AVLTNode<T>*& node) 
    {
        AVLTNode<T>* child = node->right_;
        node->right_ = child->left_;
        child->left_ = node;

        child->height_ = std::max(Height(child->left_), Height(child->right_)) + 1;
        node->height_ = std::max(Height(node->left_), Height(node->right_)) + 1;

        node = child;
    }

     /**
     *     10
     *    /
     *   6
     *    \
     *     8
     */
    void LeftBalance(AVLTNode<T>*& node) 
    {
        LeftRotate(node->left_);
        RightRotate(node);
    }

    /**
     *  10
     *   \
     *    15
     *    /
     *  12
     */
    void RightBalance(AVLTNode<T>*& node) 
    {
        RightRotate(node->right_);
        LeftRotate(node);
    }

private:
    AVLTNode<T> *root_;
};


#endif