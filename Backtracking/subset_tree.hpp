#ifndef SUBSET_TREE_SELECT_NUMBERS_HPP
#define SUBSET_TREE_SELECT_NUMBERS_HPP

#include <iostream>
#include <vector>

class SubsetTree
{
public:
    /**
        给定一组整数，从里面挑出一组数，让被选择的整数的和，跟剩下的整数的和的差值最小，并输出被选择和未被选择的数。
    */
    unsigned int SelectNumbers(const std::vector<int>& data, std::vector<bool>& selected_pos) const
    {
        if (data.size() == 0 || data.size() != selected_pos.size())
            throw std::invalid_argument("data size is 0 or selected_pos size is not equal to data size");

        std::vector<bool> temp_selected_pos(data.size());
        unsigned int  min_diff = INT_MAX;

        GetMinDiff(data, temp_selected_pos, 0, min_diff, selected_pos);

        return min_diff;
    }
    
    /**
        使用给定的整数集合(不重复)，生成全部的子集。
    */
    void  GetSubsets(const std::vector<int>& data, std::vector<std::vector<int>>& subsets) const
    {
         if (data.size() == 0)
            throw std::invalid_argument("data size is 0");

        std::vector<bool> selected_pos(data.size());
        GetSubsets(data, 0, selected_pos, subsets);
    }

    /**
        给定2N个整数，从里面挑出N个整数，让选择整数的和，和剩下的整数的和的差值最小，并输出被选择的数。
    */
    unsigned int SelectNFrom2N(const std::vector<int>& data, std::vector<bool>& selected_pos) const
    {
        if (data.size() == 0 || data.size() % 2 != 0 || data.size() != selected_pos.size())
            throw std::invalid_argument("data size is 0 or data size is not even or selected_pos size is not equal to data size");

        std::vector<bool> temp_selected_pos(data.size());
        unsigned int  min_diff = INT_MAX;

        GetMinDiff(data, temp_selected_pos, 0, min_diff, selected_pos);

        return min_diff;
    }

private:
    void GetSubsets(const std::vector<int>& data, size_t index, std::vector<bool> selected_pos, std::vector<std::vector<int>>& subsets) const
    {
        if (index == data.size())
        {
            std::vector<int> subset;
            for (size_t i = 0, size = data.size(); i < size; i++)
            {
                if (selected_pos[i])
                    subset.push_back(data[i]);
            }

            if (subset.size() > 0)
                subsets.push_back(subset);
        }
        else
        {
            selected_pos[index] = true;
            GetSubsets(data, index + 1, selected_pos, subsets);

            selected_pos[index] = false;
            GetSubsets(data, index + 1, selected_pos, subsets);
        }
    }

    void GetMinDiff(const std::vector<int>& data, std::vector<bool>& temp_selected_pos, size_t index, unsigned int& min_diff, std::vector<bool>& final_selected_pos) const
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

    void GetMinDiffN2N(const std::vector<int>& data, std::vector<bool>& temp_selected_pos, size_t index, unsigned int& min_diff, std::vector<bool>& final_selected_pos) const
    {
        size_t selected_count = std::count(temp_selected_pos.begin(), temp_selected_pos.end(), true);

        if (index == data.size())
        {
            if (selected_count == data.size() / 2)
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
        }
        else
        {
            // 左剪枝
            if (selected_count < data.size() / 2)
            {
                temp_selected_pos[index] = true;
                GetMinDiffN2N(data, temp_selected_pos, index + 1, min_diff, final_selected_pos);
                temp_selected_pos[index] = false;
            }

            // 右剪枝
            if (selected_count + (data.size() - index - 1) >= (data.size() / 2))
                 GetMinDiffN2N(data, temp_selected_pos, index + 1, min_diff, final_selected_pos);
        }
    }

};

#endif