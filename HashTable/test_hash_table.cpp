#include <iostream>
#include <gtest/gtest.h>
#include "hash_table.hpp"
#include "linked_list_hash_table.hpp"
#include "linear_probing_hash_table.hpp"

void TestCase(HashTable* hash_table)
{
    const size_t size = 100;

    for (size_t i = 0; i < size; i++)
    {
        hash_table->Insert(i);
        EXPECT_EQ(hash_table->Find(i), true);
    }

    for (size_t i = 0; i < size; i++)
    {
        hash_table->Erase(i);
        EXPECT_EQ(hash_table->Find(i), false);
    }
}

int main() 
{
    std::cout << "test_hash_table..." << std::endl;

    HashTable* ll_hash_table = new LLHashTable();
    TestCase(ll_hash_table);
   
    HashTable* lp_hash_table = new LPHashTable();
    TestCase(lp_hash_table);

    std::cout << "test done!" << std::endl;
    
    return 0;
}