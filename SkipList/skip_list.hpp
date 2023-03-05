#ifndef SKIP_LIST_HPP
#define SKIP_LIST_HPP
#include <iostream>
#include <vector>

template<typename T>
struct Node
{
    int key_;
    T value_;
    std::vector<Node *> nexts_;

    Node(int key, T value, int level)
        : key_(key)
        , value_(value)
    {
       for (int i = 0; i < level; i++)
            nexts_.push_back(nullptr); 
    }
};


template<typename T>
class SkipList
{
public:
    SkipList() : curr_highest_level_(0)
    {
        head_ = new Node<T>(INT_MIN, INT_MIN, kMaxLevel);
    }

    ~SkipList()
    {
        delete head_;
    }

    Node<T>* Find(int key)
    {
        Node<T>* iter = head_;

        for (int i = curr_highest_level_ - 1; i >= 0; --i)
        {
            while (iter->nexts_[i] && iter->nexts_[i]->key_ < key)
                iter = iter->nexts_[i];

            if (iter->nexts_[i] && iter->nexts_[i]->key_ == key)
                return iter->nexts_[i];
        }

        return nullptr;
    }

    bool Add(int key, T value)
    {
        Node<T>* new_node = Find(key);
        if (new_node)
        {
            new_node->value_ = value;
            return true;
        }

        int rand_level = RandomLevel();
        new_node = new Node<T>(key, value, rand_level);
        Node<T>* iter = head_;

        curr_highest_level_ = std::max(curr_highest_level_, rand_level);

        for (int i = curr_highest_level_ - 1; i >= 0; --i)
        {
            while (iter->nexts_[i] && iter->nexts_[i]->key_ < key)
                iter = iter->nexts_[i];

            if (i < rand_level)
            {
                new_node->nexts_[i] = iter->nexts_[i];
                iter->nexts_[i] = new_node;
            }
        }


        return false;
    }

    bool Delete(int key)
    {
        if (!Find(key))
            return false;

        Node<T>* iter = head_;
        Node<T>* del = nullptr;

        for (int i = curr_highest_level_ - 1; i >= 0; --i) {
            while (iter->nexts_[i] && iter->nexts_[i]->key_ < key) {
                iter = iter->nexts_[i];
            }
            
            del = iter->nexts_[i];
            iter->nexts_[i] = del->nexts_[i];
            
            if(!head_->nexts_[i])
                curr_highest_level_ = i;
        }

        if (del)
            delete del;

        return true;
    }

private:
    int RandomLevel() 
    {
        int random_level = 1;

//        std::srand(std::time(0)); 
        
        while (rand() % 2 == 1 && random_level <= kMaxLevel)
            ++random_level;
        
        return random_level;
    }


private:
    Node<T>* head_;
    int curr_highest_level_;
    const int kMaxLevel = 16;
};


#endif