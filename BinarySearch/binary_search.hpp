#ifndef BINARY_SEARCH_HPP
#define BINARY_SEARCH_HPP

int binary_search(const int data[], int size_of_data, int value)
{
    if (data == nullptr)
        return -1;

    int start = 0;
    int end = size_of_data - 1;

    while (start <= end)
    {
        int mid = (start + end) / 2;

        if (data[mid] == value)
            return mid;
        else if (data[mid] < value)
            start = mid + 1;
        else
            end = mid - 1;
    }

    return -1;
}

int _bianry_search_recursively(const int data[], int start, int end, int value)
{
    if (start > end)
        return -1;

    int mid = (start + end) / 2;

    if (data[mid] == value)
        return mid;
    else if (data[mid] < value)
        return _bianry_search_recursively(data, mid + 1, end, value);
    else
        return _bianry_search_recursively(data, start, mid - 1, value);
} 

int bianry_search_recursively(const int data[], int size_of_data, int value)
{
    if (data == nullptr)
        return -1;

    return _bianry_search_recursively(data, 0, size_of_data - 1, value);

}

#endif