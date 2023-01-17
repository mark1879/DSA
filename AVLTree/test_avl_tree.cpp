#include "recursive_avl_tree.hpp"
#include "non_recursive_avl_tree.hpp"
#include <gtest/gtest.h>

enum class Implementation
{
    Recursion,
    Nonrecursion
};

void CheckInOrder(const AVLTree<int>* tree, const std::vector<int>& source_in_order_keys)
{
    std::vector<int> keys;
    tree->InOrder(keys);

    EXPECT_EQ(source_in_order_keys.size(), keys.size());

    for (int i = 0, size = (int)keys.size(); i < size; i++) {
        EXPECT_EQ(source_in_order_keys[i], keys[i]);
    }
}

void TestRemoval(std::vector<int> source_keys, std::vector<int> source_in_order_keys, int reomve_key, Implementation impl)
{
    EXPECT_EQ(source_keys.size(), source_in_order_keys.size());

    AVLTree<int>* tree = nullptr;
    if (impl == Implementation::Recursion)
        tree = new RAVLTree<int>();
    else if (impl == Implementation::Nonrecursion)
        tree = new NRAVLTree<int>();

    for (auto key : source_keys)
    {
        tree->Insert(key);
        EXPECT_EQ(tree->Query(key), true);
        EXPECT_EQ(tree->IsBalance(), true);
    }

    tree->Remove(reomve_key);
    EXPECT_EQ(tree->Query(reomve_key), false);
    source_in_order_keys.erase(std::find(source_in_order_keys.begin(), source_in_order_keys.end(), reomve_key));
    CheckInOrder(tree, source_in_order_keys);
    EXPECT_EQ(tree->IsBalance(), true);

    delete tree;
}

void TestInsertion(std::vector<int> source_keys, std::vector<int> source_in_order_keys, Implementation impl) 
{
    EXPECT_EQ(source_keys.size(), source_in_order_keys.size());

    AVLTree<int>* tree = nullptr;
    if (impl == Implementation::Recursion)
        tree = new RAVLTree<int>();
    else if (impl == Implementation::Nonrecursion)
        tree = new NRAVLTree<int>();

    for (auto key : source_keys) {
        tree->Insert(key);
        EXPECT_EQ(tree->Query(key), true);
        EXPECT_EQ(tree->IsBalance(), true);
    }

    CheckInOrder(tree, source_in_order_keys);

    delete tree;
}

void Test(Implementation impl)
{
    // right rotate
    TestInsertion({10, 6, 3}, {3, 6, 10}, impl);

    // left rotate
    TestInsertion({10, 15, 20}, {10, 15, 20}, impl);

    // left balance
    TestInsertion({10, 6, 8}, {6, 8, 10}, impl);

    // right balance
    TestInsertion({10, 15, 12}, {10, 12, 15}, impl);

    // right balance
    TestInsertion({10, 6, 15, 3, 8, 7}, {3, 6, 7, 8, 10, 15}, impl);

    // left balance
    TestInsertion({10, 15, 8, 20, 13, 14}, {8, 10, 13, 14, 15, 20}, impl);


    // delete left child, right balance
    TestRemoval({10, 6, 15, 3, 8, 13, 18, 7}, {3, 6, 7, 8, 10, 13, 15, 18}, 3, impl);

    // delete left child, left rotate
    TestRemoval({10, 6, 15, 3, 8, 13, 18, 9}, {3, 6, 8, 9, 10, 13, 15, 18}, 3, impl);

    // delete right child, right rotate
    TestRemoval({10, 6, 15, 3, 8, 13, 18, 12}, {3, 6, 8, 10, 12, 13, 15, 18}, 18, impl);

    // delete right child, left balance
    TestRemoval({10, 6, 15, 3, 8, 13, 18, 14}, {3, 6, 8, 10, 13, 14, 15, 18}, 18, impl);

    // delete a node that no child
    TestRemoval({10}, {10}, 10, impl);
    TestRemoval({10, 6}, {6, 10}, 6, impl);
    TestRemoval({10, 15}, {10, 15}, 15, impl);

    // delete a node which has left child
    TestRemoval({10, 6}, {6, 10}, 6, impl);

    // delete a node which has right child
    TestRemoval({10, 15}, {10, 15}, 15, impl);

    // delete a node which has left child and right child
    TestRemoval({10, 6, 15}, {10, 6, 15}, 10, impl);
}


int main() 
{
    std::cout << "<<<<<< test_avl_tree..." << std::endl;

    Test(Implementation::Recursion);
    Test(Implementation::Nonrecursion);

    std::cout << "test done!" << std::endl;

    return 0;
}