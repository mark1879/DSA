#include "recursive_avl_tree.hpp"
#include <gtest/gtest.h>

enum class Implementation
{
    Recursion,
    Nonrecursion
};

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

void TestRemoval(Implementation impl)
{   
    std::vector<int> keys = {1, 2, 3, 4, 5, 6, 7, 8, 9};

    AVLTree<int>* tree = nullptr;
    if (impl == Implementation::Recursion)
        tree = new RAVLTree<int>();

    for (auto key : keys)
        tree->Insert(key);
    
    RemoveKey(tree, keys, 1);
    RemoveKey(tree, keys, 2);
    RemoveKey(tree, keys, 6);
    RemoveKey(tree, keys, 8);

    delete tree;
}

void TestInsertion(std::vector<int> keys, std::vector<int> in_order_keys, Implementation impl) 
{
    AVLTree<int>* tree = nullptr;
    if (impl == Implementation::Recursion)
        tree = new RAVLTree<int>();

    for (auto key : keys) {
        tree->Insert(key);
        EXPECT_EQ(tree->Query(key), true);
        EXPECT_EQ(tree->IsBalance(), true);
    }

    CheckInOrder(tree, in_order_keys);

    delete tree;
}

void Test(Implementation impl)
{
    TestInsertion({10, 6, 3}, {3, 6, 10}, impl);
    TestInsertion({10, 6, 15, 3, 8, 7}, {3, 6, 7, 8, 10}, impl);
    TestInsertion({10, 15, 20}, {10, 15, 20}, impl);
    TestInsertion({10, 15, 8, 20, 14, 13}, {8, 10, 13, 14, 15, 20}, impl);
    TestInsertion({10, 6, 8}, {6, 8, 10}, impl);
    TestInsertion({10, 15, 12}, {10, 12, 15}, impl);

    TestRemoval(impl);
}


int main() 
{
    std::cout << "<<<<<< test_avl_tree..." << std::endl;

    Test(Implementation::Recursion);

    std::cout << "test done!" << std::endl;

    return 0;
}