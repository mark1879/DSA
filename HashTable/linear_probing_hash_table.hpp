#ifndef LINEAR_PROBING_HASH_TABLE_HPP
#define LINEAR_PROBING_HASH_TABLE_HPP
#include "hash_table.hpp"

enum class BucketState
{
    kUnused,
    kUsing,
    kDeleted
};

struct Bucket
{
    Bucket() : key_(0), state_(BucketState::kUnused)
    { }

    Bucket(int key, BucketState state) 
        : key_(key) 
        , state_(state)
    { }

    size_t key_;
    BucketState state_;
};

class LPHashTable : public HashTable {
public:
    LPHashTable(double load_factor = 0.75)
        : used_bucket_num_(0)
        , load_factor_(load_factor)
        , prime_index_(0)
    {
        load_factor_ = std::max(load_factor_, 0.5);
        load_factor_ = std::min(load_factor_, 0.99);

        table_size_ = primes_[prime_index_];
        table_ = new Bucket[table_size_];
    }

    ~LPHashTable()
    {
        delete table_;
        table_ = nullptr;
    }

    bool Insert(size_t key)
    {
        double factor = used_bucket_num_ * 1.0 / table_size_;
        if (factor > load_factor_)
            Expand();

        size_t index = key % table_size_;
        size_t probe_index = index;

        do
        {
            if (table_[probe_index].state_ != BucketState::kUsing)
            {
                table_[probe_index].state_ = BucketState::kUsing;
                table_[probe_index].key_ = key;
                ++used_bucket_num_;
                return true;
            }

            probe_index = ++probe_index % table_size_;
        } while (probe_index != index);

        return false;
    }

    void Erase(size_t key)
    {
        size_t index = key % table_size_;
        size_t probe_index = index;

        do 
        {
            if (table_[probe_index].state_ == BucketState::kUsing 
                && table_[probe_index].key_ == key)
            {
                table_[probe_index].state_ = BucketState::kDeleted;
                used_bucket_num_--;
            }

            probe_index = ++probe_index % table_size_;
        } while (probe_index != index && table_[probe_index].state_ != BucketState::kUnused);
    }

    bool Find(size_t key) const
    {
        size_t index = key % table_size_;
        size_t probe_index = index;

        do
        {
            if (table_[probe_index].state_ == BucketState::kUsing
                && table_[probe_index].key_ == key)
            {   
                return true;
            }

            probe_index = ++probe_index % table_size_;
        } while (probe_index != index && table_[probe_index].state_ != BucketState::kUnused);

        return false;
    }

private:
    void Expand()
    {
        ++prime_index_;

        if (prime_index_ == kPrimeSize)
             throw("hash table can't be expanded!");

        size_t new_table_size = primes_[prime_index_];
        Bucket* new_table = new Bucket[new_table_size];

        for (size_t i = 0; i < table_size_; i++)
        {
            if(table_[i].state_ == BucketState::kUsing)
            {
                size_t index = table_[i].key_ % new_table_size;
                size_t probe_index = index;

                do
                {
                    if (new_table[probe_index].state_ != BucketState::kUsing)
                    {
                        new_table[probe_index].state_ = BucketState::kUsing;
                        new_table[probe_index].key_ = table_[i].key_;
                        break;
                    }

                    probe_index = ++probe_index % new_table_size;
                } while (probe_index != index);     // There will be no situation where the storage location cannot be found
            }
        }

        delete[] table_;
        table_ = new_table;
        table_size_ = new_table_size;
    }

private:
    Bucket *table_;
    size_t table_size_;
    size_t used_bucket_num_;
    double load_factor_;
    size_t prime_index_;

    static const size_t kPrimeSize = 10;
    static size_t primes_[kPrimeSize];
};

size_t LPHashTable::primes_[kPrimeSize] = {3, 7, 23, 47, 97, 251, 443, 911, 1471, 42773};

#endif