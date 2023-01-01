#include "binary_search_tree.hpp"
#include "recursive_binary_search_tree.hpp"
#include "non_recursive_binary_search_tree.hpp"
#include <iostream>
#include <vector>
#include <gtest/gtest.h>

void CreateBSTree(BSTree<int>*& tree, const std::vector<int>& keys, int left, int right) 
{
    if (left > right)
        return;

    // 总是选择中间位置右边的数字作为根节点
    int mid = (left + right + 1) / 2;
    tree->Insert(keys[mid]);

    CreateBSTree(tree, keys, left, mid - 1);
    CreateBSTree(tree, keys, mid + 1, right);
}

void CheckInOrder(BSTree<int>* tree, const std::vector<int>& keys)
{
    std::vector<int> in_order_keys;
    tree->InOrder(in_order_keys);

    for (int i = 0, size = (int)keys.size(); i < size; i++)
        EXPECT_EQ(in_order_keys[i], keys[i]);

    // std::cout << "InOrder: " << std::endl;
    // for (auto it : in_order_keys)
    //     std::cout << it << "\t";

    // std::cout << std::endl;

    // std::cout << "PreOrder: " << std::endl;
    // std::vector<int> pre_order_keys;
    // tree->PreOrder(pre_order_keys);
    // for (auto it : pre_order_keys)
    //     std::cout << it << "\t";

    // std::cout << std::endl;

    // std::cout << "PostOrder: " << std::endl;
    // std::vector<int> post_order_keys;
    // tree->PostOrder(post_order_keys);
    // for (auto it : post_order_keys)
    //     std::cout << it << "\t";

    // std::cout << std::endl;
}


void Test(BSTree<int>*& tree, std::vector<int> keys) 
{
    CreateBSTree(tree, keys, 0, keys.size() - 1);
    for (int i = 0, size = (int)keys.size(); i < size; i++)
        EXPECT_EQ(tree->Query(keys[i]), true);
    CheckInOrder(tree, keys);

    tree->Remove(1);
    EXPECT_EQ(tree->Query(1), false);
    keys.erase(std::find(keys.begin(), keys.end(), 1));
    CheckInOrder(tree, keys);

    tree->Remove(3);
    EXPECT_EQ(tree->Query(3), false);
    keys.erase(std::find(keys.begin(), keys.end(), 3));
    CheckInOrder(tree, keys);

    tree->Remove(6);
    EXPECT_EQ(tree->Query(6), false);
    keys.erase(std::find(keys.begin(), keys.end(), 6));
    CheckInOrder(tree, keys);

    tree->Remove(4);
    EXPECT_EQ(tree->Query(4), false);
    keys.erase(std::find(keys.begin(), keys.end(), 4));
    CheckInOrder(tree, keys);
}


int main() {

    std::cout << "<<<<<< test_binary_search_tree..." << std::endl;

    std::vector<int> data = {1, 2, 3, 4, 5, 6, 7};

    BSTree<int>* recursive_bst_tree = new RBSTree<int>();
    Test(recursive_bst_tree, data);

    BSTree<int>* non_recursive_bst_tree = new NRBSTree<int>();
    Test(non_recursive_bst_tree, data);

    std::cout << "test done!" << std::endl << std::endl;

    return 0;
}