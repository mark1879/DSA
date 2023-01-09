#include "recursive_avl_tree.hpp"
#include <gtest/gtest.h>

void CheckInOrder(const AVLTree<int>* tree, const std::vector<int>& keys)
{
    std::vector<int> in_order_keys;
    tree->InOrder(in_order_keys);

    for (int i = 0, size = (int)keys.size(); i < size; i++) 
        EXPECT_EQ(in_order_keys[i], keys[i]);
}

void RemoveKey(AVLTree<int>* tree, std::vector<int>& keys, int key)
{
    tree->Remove(key);
    EXPECT_EQ(tree->Query(key), false);
    keys.erase(std::find(keys.begin(), keys.end(), key));
    CheckInOrder(tree, keys);
    EXPECT_EQ(tree->IsBalance(), true);
}

void Test(AVLTree<int>*& tree, std::vector<int> keys) 
{
    for (auto key : keys) {
        tree->Insert(key);
        EXPECT_EQ(tree->Query(key), true);
        EXPECT_EQ(tree->IsBalance(), true);
    }

    CheckInOrder(tree, keys);

    RemoveKey(tree, keys, 1);
    RemoveKey(tree, keys, 2);
    RemoveKey(tree, keys, 6);
    RemoveKey(tree, keys, 8);
}


int main() 
{
    std::cout << "<<<<<< test_avl_tree..." << std::endl;

    AVLTree<int>* recursive_avl_tree = new RAVLTree<int>();
    Test(recursive_avl_tree, {1, 2, 3, 4, 5, 6, 7, 8, 9});
    delete recursive_avl_tree;

    std::cout << "test done!" << std::endl;

    return 0;
}