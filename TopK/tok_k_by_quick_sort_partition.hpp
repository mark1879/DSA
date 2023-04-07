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

        SelectTopKNums(data, 0, data.size() - 1, k);

        return std::vector<int>(data.begin(), data.begin() + k);
    }

private:
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
        int pivot = data[begin];
        size_t i = begin;
        size_t j = end;

        while (i != j)
        {
            while (data[j] > pivot && i < j)
                j--;

            while (data[i] <= pivot && i < j)
                i++;

            if (i < j)
                std::swap(data[i], data[j]);
        }

        data[begin] = data[i];
        data[i] = pivot;

        return i;
    }
};


#endif