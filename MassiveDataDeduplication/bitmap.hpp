#ifndef BITMAP_HPP
#define BITMAP_HPP
#include <vector>

class Bitmap
{
public:
    Bitmap(const std::vector<unsigned int>& keys)
        : keys_(keys)
    {
        int max = 0;
        for (const auto& key : keys)
        {
            if (key > max)
                max = key; 
        }

        bitmap_ = new unsigned int[max / 32 + 1];

        for (const auto& key : keys)
        {
            size_t index = key / 32;
            size_t offset = key % 32;

            bitmap_[index] |= (1 << offset);
        }
    }

    ~Bitmap()
    { 
        delete[] bitmap_;
    }

    bool Exist(unsigned int key)
    {
        size_t index = key / 32;
        size_t offset = key % 32;

        return bitmap_[index] & (1 << offset);
    }

private:
    std::vector<unsigned int> keys_;
    unsigned int* bitmap_;
};
#endif