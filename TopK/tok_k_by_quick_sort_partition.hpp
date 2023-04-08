#ifndef TOP_K_BY_QUICK_SORT_PARTITION_HPP
#define TOP_K_BY_QUICK_SORT_PARTITION_HPP

// top k by quick sort partition
class TopKByQSP
{
public:
    std::vector<int> GetTopKMinNums(std::vector<int>& data, size_t k)
    {
         if (k > data.size() || k == 0)
            throw "k is greater than data size or is equals to 0";

        if (k == data.size())
            return data;

        GetTopKMinNums_(data, 0, data.size() - 1, k);

        return std::vector<int>(data.begin(), data.begin() + k);
    }

    int GetKthMinNum(std::vector<int>& data, size_t kth)
    {
         if (kth > data.size() || kth == 0)
            throw "kth is greater than data size or is equals to 0";

        return GetKthMinNum_(data, 0, data.size() - 1, kth);
    }

private:
    int GetKthMinNum_(std::vector<int>& data, size_t begin, size_t end, size_t kth)
    {
        size_t pivot = Partition(data, begin, end);

        if (pivot == kth - 1)
            return data[pivot];
        else if (pivot < kth - 1)
            return GetKthMinNum_(data, pivot + 1, end, kth);
        else
            return GetKthMinNum_(data, begin, pivot - 1, kth);

    }

    void GetTopKMinNums_(std::vector<int>& data, size_t begin, size_t end, size_t k)
    {
        size_t pivot = Partition(data, begin, end);

        if (pivot == k - 1)
            return;
        else if (pivot > k - 1)
        {
            GetTopKMinNums_(data, begin, pivot - 1, k);
        }
        else
        {
            GetTopKMinNums_(data, pivot + 1, end, k);
        }
    }

    size_t Partition(std::vector<int>& data, size_t begin, size_t end)
    {
        int pivot_val = data[begin];
        size_t i = begin;
        size_t j = end;

        while (i < j)
        {
            while (data[j] > pivot_val && i < j)
                j--;

            while (data[i] <= pivot_val && i < j)
                i++;

            if (i < j)
                std::swap(data[i], data[j]);
        }

        data[begin] = data[i];
        data[i] = pivot_val;

        return i;
    }
};


#endif