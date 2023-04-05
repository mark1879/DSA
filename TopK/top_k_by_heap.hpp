#ifndef TOP_K_BY_HEAP_HPP
#define TOP_K_BY_HEAP_HPP
#include <vector>
#include <queue>
#include <map>
#include <iostream>

class TopKByHeap 
{
public:
    std::vector<int> GetTopKMinNums(const std::vector<int>& data, size_t k)
    {
        if (k > data.size() || k == 0)
            throw "k is greater than data size or is equals to 0";

        if (k == data.size())
            return data;

        std::vector<int> max_heap(data.begin(), data.begin() + k);
        
        for (int i = (k - 1) / 2; i >= 0; i--)
            ShiftDown(max_heap, i);

        for (size_t i = k, size = data.size(); i < size; i++)
        {
            if (data[i] < max_heap[0])
            {
                max_heap[0] = data[i];
                ShiftDown(max_heap, 0);
            }
        }

        return max_heap;
    }

    std::vector<int> GetTopKMinNums2(const std::vector<int>& data, size_t k)
    {
        if (k > data.size() || k == 0)
            throw "k is greater than data size or is equals to 0";

        if (k == data.size())
            return data;

        // std::priority_queue<int> max_heap(data.begin(), data.begin() + k);

        // Second way to define a max priority queue
        std::priority_queue<int, std::vector<int>, std::less<int>> max_heap(data.begin(), data.begin() + k); 

        for (size_t i = k, size = data.size(); i < size; i++)
        {
            if (data[i] < max_heap.top())
            {
                max_heap.pop();
                max_heap.push(data[i]);
            }
        }

        std::vector<int> top_k_min_nums;

        while (!max_heap.empty())
        {
            top_k_min_nums.push_back(max_heap.top());
            max_heap.pop();
        }

        return top_k_min_nums;
    }

    std::vector<int> GetTopKMinRepetitionNums(const std::vector<int>& data, size_t k)
    {
        std::map<int, int> num_counts;
        for (auto key : data)
        {
            num_counts[key]++;
        }

        if (k > num_counts.size() || k == 0)
            throw "k is greater than the size of unduplicated numbers or is equals to 0";

        using Type = std::pair<int, int>;
        using Comp = std::function<bool(Type&, Type&)>;
        std::priority_queue<Type, std::vector<Type>, Comp> max_heap(
            [](Type& a, Type& b)->bool {
                return a.second < b.second;
            }
        );

        auto it = num_counts.begin();
        for (size_t i = 0; i < k; ++i, ++it)
            max_heap.push(*it);

        for (; it != num_counts.end(); ++it)
        {
            if (it->second < max_heap.top().second)
            {
                max_heap.pop();
                max_heap.push(*it);
            }
        }

        std::vector<int> top_k_min_nums;
        while (!max_heap.empty())
        {
            top_k_min_nums.push_back(max_heap.top().first);
            max_heap.pop();
        }

        return top_k_min_nums;
    }


private:
    // build max heap
    void ShiftDown(std::vector<int>& data, int adjusted_pos)
    {
        int size = (int)data.size();
        
        while (adjusted_pos * 2 + 1 < size)
        {
            int bigger_child = adjusted_pos * 2 + 1;

            if (bigger_child + 1 < size && data[bigger_child + 1] > data[bigger_child])
                bigger_child = bigger_child + 1;

            if (data[bigger_child] > data[adjusted_pos])
                std::swap(data[bigger_child], data[adjusted_pos]);

            adjusted_pos = bigger_child;
        }
    }

};


#endif