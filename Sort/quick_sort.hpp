#ifndef QUICK_SORT_HPP
#define QUICK_SORT_HPP

void quick_sort_(int* data, int left, int right)
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

    quick_sort_(data, left, i - 1);
    quick_sort_(data, i + 1, right);
}

bool quick_sort(int* data, int size_of_data)
{
    if (data == nullptr)
        return false;

    quick_sort_(data, 0, size_of_data - 1);

    return true;
}


#endif