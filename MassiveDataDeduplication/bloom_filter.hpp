#ifndef BLOOM_FILTER_HPP
#define BLOOM_FILTER_HPP
#include <iostream>
#include <vector>
#include "string_hash.h"
#include <string>

class BloomFilter
{
public:
    BloomFilter(size_t bit_size = 3001)
        : bit_size_(bit_size)
    {
        bit_map_.resize(bit_size_ / 32 + 1);
    }

    void SetBit(const std::string& str)
    {
        std::vector<size_t> hash = GenerateHash(str);

        for (const auto& it : hash)
        {
            int index = it / 32;
            int offset = it % 32;

            bit_map_[index] |= (1 << offset);
        }
    }

    bool GetBit(const std::string& str)
    {
        std::vector<size_t> hash = GenerateHash(str);

        for (const auto& it : hash)
        {
            int index = it / 32;
            int offset = it % 32;

            if (0 == (bit_map_[index] & (1 << offset)))
                return false;
        }

        return true;
    }

private:
    std::vector<size_t> GenerateHash(const std::string& str)
    {
        size_t index1 = BKDRHash(str.c_str()) % bit_size_;
        size_t index2 = RSHash(str.c_str()) % bit_size_;

        return {index1, index2};
    }

private:
    size_t bit_size_;
    std::vector<size_t> bit_map_;
};


#endif