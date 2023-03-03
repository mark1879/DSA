#include <iostream>
#include <gtest/gtest.h>
#include "linked_list_hash_table.hpp"

int main() 
{
    std::cout << "test_hash_table..." << std::endl;

    HashTable* ll_hash_table = new LLHashTable();

    const size_t size = 100;

    for (size_t i = 0; i < size; i++)
    {
        ll_hash_table->Insert(i);
        EXPECT_EQ(ll_hash_table->Find(i), true);
    }

    for (size_t i = 0; i < size; i++)
    {
        ll_hash_table->Erase(i);
        EXPECT_EQ(ll_hash_table->Find(i), false);
    }

    std::cout << "test done!" << std::endl;
    
    return 0;
}