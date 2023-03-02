#ifndef QUICK_SORT_HPP
#define QUICK_SORT_HPP
#include <algorithm>
#include <iostream>

// get the median from three nums as the pivot
int _GetPivot(int data[], int left, int right)
{
    int mid = (left + right) / 2;
    
    if (data[mid] > data[right])
        std::swap(data[mid], data[right]);
    
    if (data[left] < data[mid])
        std::swap(data[left], data[mid]);
    
    if (data[left] > data[right])
        std::swap(data[left], data[right]);
    
    return left;
}

void _QuickSort2(int* data, int left, int right)
{
    if (left >= right)
        return;

    int pivot = _GetPivot(data, left, right);
    int i = left;
    int j = right;

    while (i < j)
    {
        while (data[j] >= data[pivot] && i < j)
            j--;

        while (data[i] <= data[pivot] && i < j)
            i++;

        if (i < j)
            std::swap(data[i], data[j]);
    }

    std::swap(data[pivot], data[i]);

    _QuickSort2(data, left, i - 1);
    _QuickSort2(data, i + 1, right);
}

bool QuickSort2(int* data, int size_of_data)
{
    if (data == nullptr || size_of_data <= 0)
        return false;

    _QuickSort2(data, 0, size_of_data - 1);

    return true;
}


void _QuickSort(int* data, int left, int right)
{
    if (left >= right)
        return;

    int i = left;
    int j = right;

    while (i < j)
    {
        while (data[j] >= data[left] && i < j)
            j--;

        while (data[i] <= data[left] && i < j)
            i++;

        if (i < j)
            std::swap(data[i], data[j]);
    }

    std::swap(data[left], data[i]);

    _QuickSort(data, left, i - 1);
    _QuickSort(data, i + 1, right);
}

bool QuickSort(int* data, int size_of_data)
{
    if (data == nullptr || size_of_data <= 0)
        return false;

    _QuickSort(data, 0, size_of_data - 1);

    return true;
}


#endif