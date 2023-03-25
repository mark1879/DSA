#ifndef SUBSET_TREE_SELECT_NUMBERS_HPP
#define SUBSET_TREE_SELECT_NUMBERS_HPP

#include <iostream>
#include <vector>

class SelectNumbers
{
public:
    unsigned int GetMinDiff(std::vector<int>& data, std::vector<bool>& selected_pos)
    {
        std::vector<bool> temp_selected_pos(data.size());
        unsigned int  min_diff = INT_MAX;

        GetMinDiff(data, temp_selected_pos, 0, min_diff, selected_pos);

        return min_diff;
    }

private:
    void GetMinDiff(std::vector<int>& data, std::vector<bool>& temp_selected_pos, size_t index, unsigned int& min_diff, std::vector<bool>& final_selected_pos)
    {
        if (index == data.size())
        {
            int sum_selected_nums = 0;
            int sum_unselected_nums = 0;

            for (size_t i = 0, size = data.size(); i < size; i++)
            {
                if (temp_selected_pos[i])
                    sum_selected_nums += data[i];
                else 
                    sum_unselected_nums += data[i];
            }

            if (abs(sum_selected_nums - sum_unselected_nums) < min_diff)
            {
                min_diff = abs(sum_selected_nums - sum_unselected_nums);
                final_selected_pos = temp_selected_pos;
            }
        }
        else
        {
            temp_selected_pos[index] = true;
            GetMinDiff(data, temp_selected_pos, index + 1, min_diff, final_selected_pos);

            temp_selected_pos[index] = false;
            GetMinDiff(data, temp_selected_pos, index + 1, min_diff, final_selected_pos);
        }
    }
};

#endif