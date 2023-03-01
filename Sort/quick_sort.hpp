#ifndef QUICK_SORT_HPP
#define QUICK_SORT_HPP

void _QuickSort(int* data, int left, int right)
{
    if (left >= right)
        return;

    int middle = data[left];
    int i = left;
    int j = right;

    while (i < j)
    {
        while (data[j] >= middle && i < j)
            j--;

        while (data[i] <= middle && i < j)
            i++;

        if (i < j)
        {
            int temp = data[i];
            data[i] = data[j];
            data[j] = temp;
        }
    }

    data[left] = data[i];
    data[i] = middle;

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