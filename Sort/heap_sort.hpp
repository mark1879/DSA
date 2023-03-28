#ifndef HEAP_SORT_HPP
#define HEAP_SORT_HPP
#include <algorithm>
#include <iostream>

void _ShiftDown(int* data, int size_of_data, int adjusted_pos)
{   
    while (2 * adjusted_pos + 1 < size_of_data)
    {
        int bigger_child = 2 * adjusted_pos + 1;

        if (bigger_child + 1 < size_of_data && data[bigger_child + 1] > data[bigger_child])
            bigger_child += 1;

        if (data[adjusted_pos] >= data[bigger_child])
            break;
 
        std::swap(data[adjusted_pos], data[bigger_child]);

        adjusted_pos = bigger_child;
    }
}

bool HeapSort(int* data, int size_of_data)
{
    if (data == nullptr || size_of_data <= 0)
        return false;

    // build max heap from the second-to-last layer
    for (int i = (size_of_data - 1) / 2; i >= 0; i--)
        _ShiftDown(data, size_of_data, i);

    // sort heap，find the largest element in remain data every time
    for (int i = size_of_data - 1; i > 0; i--)
    {
        std::swap(data[0], data[i]);
        _ShiftDown(data, i, 0);
    }

    return true;
}

#endif