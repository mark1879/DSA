#ifndef TOP_K_BY_HEAP_HPP
#define TOP_K_BY_HEAP_HPP
#include <vector>
#include <queue>
#include <map>
#include <iostream>

class TopKByHeap 
{
public:
    std::vector<int> GetTopKMinNums(std::vector<int>& data, size_t k)
    {
        size_t size = data.size();

        if (k > size || k == 0)
            throw "k is greater than data size or is equals to 0";

        if (k == size)
            return data;
        
        // build max heap
        for (int i = (k - 1) / 2; i >= 0; i--)
            BuidMaxHeap(data, k, i);

        for (size_t i = k; i < size; i++)
        {
            if (data[i] < data[0])
            {
                data[0] = data[i];
                BuidMaxHeap(data, k, 0);
            }
        }

        return std::vector<int>(data.begin(), data.begin() + k);
    }

    std::vector<int> GetTopKMinNums2(std::vector<int>& data, size_t k)
    {
        size_t size = data.size();

        if (k > size || k == 0)
            throw "k is greater than data size or is equals to 0";

        if (k == size)
            return data;

        // build max heap
        // std::priority_queue<int> max_heap(data.begin(), data.begin() + k);

        // Second way to build max heap
        std::priority_queue<int, std::vector<int>, std::less<int>> max_heap(data.begin(), data.begin() + k); 

        for (size_t i = k; i < size; i++)
        {
            if (data[i] < max_heap.top())
            {
                max_heap.pop();
                max_heap.push(data[i]);
            }
        }

        std::vector<int> top_k_min_nums;
        for (size_t i = 0; i < k; i++)
        {
            top_k_min_nums.push_back(max_heap.top());
            max_heap.pop();
        }

        return top_k_min_nums;
    }

    int GetKthMinNum(std::vector<int>& data, size_t kth)
    {
         size_t size = data.size();

         if (kth > size || kth == 0)
            throw "kth is greater than data size or is equals to 0";

        for (int i = (size - 1) / 2; i >= 0; i--)
            BuildMinHeap(data, size, i);

        for (int i = 0; i < kth - 1; i++)
        {
            data[0] = data[size - 1 - i];
            BuildMinHeap(data, size - 1 - i, 0);
        }
        
        return data[0];
    }

    int GetKthMinNum2(std::vector<int>& data, size_t kth)
    {
        if (kth > data.size() || kth == 0)
            throw "kth is greater than data size or is equals to 0";

        // build min heap
        std::priority_queue<int, std::vector<int>, std::greater<int>> max_heap(data.begin(), data.end()); 

        for (size_t i = 0; i < kth - 1; i++)
            max_heap.pop();

        return max_heap.top();
    }

private:
    template<typename Comp>
    void ShiftDown(std::vector<int>& data, int size, int adjusted_pos, Comp cmp = Comp())
    {   
        while (2 * adjusted_pos + 1 < size)
        {
            int left_child = 2 * adjusted_pos + 1;

            if (left_child + 1 < size && cmp(data[left_child + 1], data[left_child]))
                left_child += 1;

            if (cmp(data[left_child], data[adjusted_pos]))
                std::swap(data[left_child], data[adjusted_pos]);

            adjusted_pos = left_child;
        }
    }

    void BuidMaxHeap(std::vector<int>& data, size_t size, int adjusted_pos)
    {
       ShiftDown<std::greater<int>>(data, size, adjusted_pos);
    }

    void BuildMinHeap(std::vector<int>& data, size_t size, int adjusted_pos)
    {
        ShiftDown<std::less<int>>(data, size, adjusted_pos);
    }
};


#endif