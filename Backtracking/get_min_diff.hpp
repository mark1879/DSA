#ifndef SELECT_NUMBERS_TO_GET_MIN_DIFF
#define SELECT_NUMBERS_TO_GET_MIN_DIFF
#include <iostream>
#include <vector>
#include <gtest/gtest.h>

class GetMinDiff
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

        MinDiff(data, temp_selected_pos, 0, min_diff, selected_pos);

        return min_diff;
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

        MinDiff2(data, temp_selected_pos, 0, min_diff, selected_pos);

        return min_diff;
    }

private:
    void MinDiff(const std::vector<int>& data, std::vector<bool>& temp_selected_pos, size_t index, unsigned int& min_diff, std::vector<bool>& final_selected_pos) const
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
            MinDiff(data, temp_selected_pos, index + 1, min_diff, final_selected_pos);

            temp_selected_pos[index] = false;
            MinDiff(data, temp_selected_pos, index + 1, min_diff, final_selected_pos);
        }
    }

    void MinDiff2(const std::vector<int>& data, std::vector<bool>& temp_selected_pos, size_t index, unsigned int& min_diff, std::vector<bool>& final_selected_pos) const
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
                MinDiff2(data, temp_selected_pos, index + 1, min_diff, final_selected_pos);
                temp_selected_pos[index] = false;
            }

            // 右剪枝
            if (selected_count + (data.size() - index - 1) >= (data.size() / 2))
                MinDiff2(data, temp_selected_pos, index + 1, min_diff, final_selected_pos);
        }
    }
};

void TestSelectNumbersByCase(const GetMinDiff& get_min_diff, std::vector<int> data, unsigned int min_diff)
{
    std::vector<bool> selected_pos(data.size());
    EXPECT_EQ(get_min_diff.SelectNumbers(data, selected_pos), min_diff);
}

void TestSelectNumbers()
{
    std::cout << "test_select_numbers..." << std::endl;

    GetMinDiff get_min_diff;

    TestSelectNumbersByCase(get_min_diff, {10}, 10);
    TestSelectNumbersByCase(get_min_diff, {10, 20}, 10);
    TestSelectNumbersByCase(get_min_diff, {10, 20, 31}, 1);
    TestSelectNumbersByCase(get_min_diff, {10, 20, 30, 11}, 9);
}

void TESTSelectNFrom2NByCase(const GetMinDiff& get_min_diff, std::vector<int> data, unsigned int min_diff)
{
    std::vector<bool> selected_pos(data.size());
    EXPECT_EQ(get_min_diff.SelectNFrom2N(data, selected_pos), min_diff);

    size_t count = 0;
    for (const auto& it : selected_pos)
        if (it == true)
            ++count;

    EXPECT_EQ(count, selected_pos.size() / 2);
}

void TESTSelectNFrom2N()
{
    std::cout << "test_select_N_from_2N..." << std::endl;

    GetMinDiff get_min_diff;

    TESTSelectNFrom2NByCase(get_min_diff, {1, 2}, 1);
    TESTSelectNFrom2NByCase(get_min_diff, {1, 2, 3, 4}, 0);
    TESTSelectNFrom2NByCase(get_min_diff, {1, 2, 3, 5}, 1);
    TESTSelectNFrom2NByCase(get_min_diff, {1, 3, 3, 5}, 0);
}

void TestGetMinDiff()
{
    TestSelectNumbers();
    TESTSelectNFrom2N();
}

#endif