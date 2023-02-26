#ifndef BUBBLE_SORT_HPP
#define BUBBLE_SORT_HPP

bool bubble_sort(int* data, int size_of_data)
{
    if (data == nullptr)
        return false;

    for (int i = 0; i < size_of_data; i++)
    {
        bool exchanged = false;

        for (int j = 0; j < size_of_data - 1 - i; j++)
        {
            if (data[j] > data[j + 1])
            {
                int temp = data[j + 1];
                data[j + 1] = data[j];
                data[j] = temp;
                exchanged = true;
            }
        }

        if (!exchanged)
            break;
    }

    return true;
}

#endif