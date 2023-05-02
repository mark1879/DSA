#include "get_min_diff.hpp"
#include "get_sub_sets.hpp"
#include "combination_sum.hpp"

int main()
{
    std::cout << "test_back_tracking..." << std::endl;

    GetMinDiff::Test();
    CombinationSum::Test();
    GetSubsets::Test();
   
    std::cout << "test done!" << std::endl << std::endl;

    return 0;
}