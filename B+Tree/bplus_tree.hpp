#ifndef BPLUS_TREE_HPP
#define BPLUS_TREE_HPP

// Searching on a B+ tree in C++

#include <climits>
#include <fstream>
#include <iostream>
#include <sstream>

using namespace std;
int kM = 3;

struct Node {
    bool is_leaf_;
    int *keys_;
    int keys_num_;
    Node **children_;

public:
    Node() {
        is_leaf_ = false;
        keys_ = new int[kM];
        //  each node can contain a maximum of m - 1 keys
        keys_num_ = 0;
        
        children_ = new Node *[kM + 1];
        for (int i = 0; i < kM + 1; i++) {
            children_[i] = nullptr;
        }
    }
};

class BPTree {
private:
    void InsertInternal(int, Node *, Node *);
    Node *FindParent(Node *, Node *);

public:
    BPTree();
    void Search(int);
    void Insert(int);
    void Display(Node *);
    Node *get_root() { return root_; };
    
private:
    Node *root_;
};

BPTree::BPTree() {
  root_ = nullptr;
}

void BPTree::Search(int x){
    if (root_ == nullptr) {
        cout << "Tree is empty\n" << endl;
    } else {
        Node *cursor = root_;
        while (!cursor->is_leaf_) {
            int i = 0;
            int keys_num = cursor->keys_num_;
            for (; i < keys_num; i++) {
                if (x < cursor->keys_[i]) {
                    cursor = cursor->children_[i];
                    break;
                }
            }
            
            // children 比 keys 最多多一个
            if (i == keys_num) {
                cursor = cursor->children_[i];
            }
        }
          
        for (int i = 0; i < cursor->keys_num_; i++) {
            if (cursor->keys_[i] == x) {
                cout << "Found\n" << endl;
                return;
            }
        }
        
        cout << "Not found\n" << endl;
  }
}

void BPTree::Insert(int x) {
    if (root_ == nullptr){
        root_ = new Node();
        root_->keys_[0] = x;
        root_->is_leaf_ = true;
        root_->keys_num_ = 1;
    } else {
        Node *cursor = root_;
        Node *parent = nullptr;
        
        while (!cursor->is_leaf_) {
            parent = cursor;
            int i = 0;
            int keys_num = cursor->keys_num_;
            for (; i < keys_num; i++) {
                if (x < cursor->keys_[i]) {
                    cursor = cursor->children_[i];
                    break;
                }
            }
            
            // children 比 keys 最多多一个
            if (i == keys_num) {
                cursor = cursor->children_[i];
            }
        }
        
        int i = 0;
        while (x > cursor->keys_[i] && i < cursor->keys_num_)
            i++;

        for (int j = cursor->keys_num_; j > i; j--)
            cursor->keys_[j] = cursor->keys_[j - 1];

        cursor->keys_[i] = x;
        cursor->keys_num_++;
        
        if (cursor->keys_num_ < kM)
            return;
        
        
        // 分裂节点
        Node *new_leaf = new Node();
        new_leaf->is_leaf_ = true;
        cursor->keys_num_ = (kM + 1) / 2 - 1;
        new_leaf->keys_num_ = kM - cursor->keys_num_ ;
        
        for (int i = 0, j = cursor->keys_num_; i < new_leaf->keys_num_ && j < kM; i++, j++)
            new_leaf->keys_[i] = cursor->keys_[j];
            
        if (cursor == root_) {
            Node *new_root = new Node();
            new_root->keys_[0] = new_leaf->keys_[0];
            new_root->children_[0] = cursor;
            new_root->children_[1] = new_leaf;
            new_root->keys_num_ = 1;
            root_ = new_root;
        } else {
            InsertInternal(new_leaf->keys_[0], parent, new_leaf);
        }
    }
}

// Insert Operation
void BPTree::InsertInternal(int x, Node *cursor, Node *child) {
    
    if (cursor == nullptr) {
        cout << "Error, cursor is nullptr" << endl;
        return;
    }
    
    int i = 0;
    while (x > cursor->keys_[i] && i < cursor->keys_num_)
        i++;

    for (int j = cursor->keys_num_; j > i; j--)
        cursor->keys_[j] = cursor->keys_[j - 1];
    
    for (int j = cursor->keys_num_ + 1; j > i + 1; j--)
        cursor->children_[j] = cursor->children_[j - 1];

    cursor->keys_[i] = x;
    cursor->children_[i + 1] = child;
    cursor->keys_num_++;
    
    if (cursor->keys_num_ < kM)
        return;
    
    // 分裂节点
    Node *new_internal = new Node();
    cursor->keys_num_ = kM / 2;
    new_internal->keys_num_ = kM - cursor->keys_num_ - 1;
    
    // 中间的一个Node必须抽取出来，上移
    for (int i = 0, j = cursor->keys_num_ + 1; i < new_internal->keys_num_ && j < kM; i++, j++)
        new_internal->keys_[i] = cursor->keys_[j];
    
    // child 最多比 key 多 1 个
    for (int i = 0, j = cursor->keys_num_ + 1; (i < new_internal->keys_num_ + 1) && (j < kM + 1); i++, j++)
        new_internal->children_[i] = cursor->children_[j];

    if (cursor == root_) {
      Node *new_root = new Node;
      new_root->keys_[0] = cursor->keys_[cursor->keys_num_];
      new_root->children_[0] = cursor;
      new_root->children_[1] = new_internal;
      new_root->keys_num_ = 1;
      root_ = new_root;
    } else {
        InsertInternal(cursor->keys_[cursor->keys_num_], FindParent(root_, cursor), new_internal);
    }
}

Node *BPTree::FindParent(Node *cursor, Node *child) {
  Node *parent = nullptr;
    
  if (cursor->is_leaf_) {
      return nullptr;
  }
    
  for (int i = 0; i < cursor->keys_num_ + 1; i++) {
    if (cursor->children_[i] == child) {
        parent = cursor;
        break;
    } else {
        parent = FindParent(cursor->children_[i], child);
        if (parent != nullptr)
            break;
    }
  }
    
  return parent;
}

void BPTree::Display(Node *cursor) {
  if (cursor != nullptr) {
    for (int i = 0; i < cursor->keys_num_; i++) {
      cout << cursor->keys_[i] << " ";
    }
    cout << "\n";
    if (!cursor->is_leaf_) {
      for (int i = 0; i < cursor->keys_num_ + 1; i++) {
        Display(cursor->children_[i]);
      }
    }
  }
}
#endif