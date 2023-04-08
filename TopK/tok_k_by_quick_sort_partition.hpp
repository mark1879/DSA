#ifndef TOP_K_BY_QUICK_SORT_PARTITION_HPP
#define TOP_K_BY_QUICK_SORT_PARTITION_HPP

// top k by quick sort partition
class TopKByQSP
{
public:
    int GetKthMinNum(std::vector<int>& data, size_t kth)
    {
         if (kth > data.size() || kth == 0)
            throw "kth is greater than data size or is equals to 0";

        return Partition(data, 0, data.size() - 1, kth);
    }

    std::vector<int> GetTopKMinNums(std::vector<int>& data, size_t k)
    {
         if (k > data.size() || k == 0)
            throw "k is greater than data size or is equals to 0";

        if (k == data.size())
            return data;

        SelectTopKNums(data, 0, data.size() - 1, k);

        return std::vector<int>(data.begin(), data.begin() + k);
    }

private:
    int Partition(std::vector<int>& data, size_t begin, size_t end, size_t kth)
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

        if (i == kth - 1)
            return data[i];
        else if (i < kth - 1)
            return Partition(data, i + 1, end, kth);
        else
            return Partition(data, begin, i - 1, kth);
    }

    void SelectTopKNums(std::vector<int>& data, size_t begin, size_t end, size_t k)
    {
        size_t pivot = Partition(data, begin, end);

        if (pivot == k - 1)
            return;
        else if (pivot > k - 1)
        {
            SelectTopKNums(data, begin, pivot - 1, k);
        }
        else
        {
            SelectTopKNums(data, pivot + 1, end, k);
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