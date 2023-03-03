#ifndef LINKED_LIST_HASH_TABLE_HPP
#define LINKED_LIST_HASH_TABLE_HPP
#include "hash_table.hpp"
#include <iostream>
#include <vector>
#include <list>

class LLHashTable : public HashTable
{
public:
    LLHashTable(double load_factor = 0.75)
    : used_bucket_num_(0)
    , load_factor_(load_factor)
    , prime_index_(0)
    {
        table_.resize(primes_[prime_index_]);
    }

    ~LLHashTable()
    {}

    void Insert(int key) override
    {
        double factor = (used_bucket_num_ * 1.0 / table_.size());
        if ( factor > load_factor_)
            Expand();

        int index = key % table_.size();
        if (table_[index].empty())
        {
            used_bucket_num_++;
            table_[index].emplace_front(key);
        }
        else
        {
            auto it = std::find(table_[index].begin(), table_[index].end(), key);
            if (it == table_[index].end())
                table_[index].emplace_front(key);
        }
    }

    void Erase(int key) override
    {
        int index = key % table_.size();
        auto it = std::find(table_[index].begin(), table_[index].end(), key);
        if (it != table_[index].end())
        {
            table_[index].erase(it);
            if (table_[index].empty())
                used_bucket_num_--;
        }
    }

    bool Find(int key) const override
    {
        int index = key % table_.size();
        auto it = std::find(table_[index].begin(), table_[index].end(), key);

        return it != table_[index].end();
    }

private:
    void Expand()
    {
        prime_index_++;
        if (prime_index_ == kPrimeNum)
            throw("hash table can't be expanded!");

        used_bucket_num_ = 0;
        std::vector<std::list<int>> new_table;
        new_table.resize(primes_[prime_index_]);

        for (const auto& list : table_)
        {
            for(const auto& key : list)
            {
                size_t index = key % new_table.size();
                if (new_table[index].empty())
                    used_bucket_num_++;

                new_table[index].emplace_front(key);
            }
        }

        table_.clear();
        table_ = new_table;
    }

private:
    std::vector<std::list<int>> table_;
    size_t used_bucket_num_;
    double load_factor_;
    size_t prime_index_;

    static const int kPrimeNum = 10;
    static size_t primes_[kPrimeNum];
};

size_t LLHashTable::primes_[kPrimeNum] = {3, 7, 23, 47, 97, 251, 443, 911, 1471, 42773};

#endif


