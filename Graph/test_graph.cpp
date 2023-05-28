#include "adjacent_matrix.hpp"
#include "adjacent_list.hpp"
#include "weighted_adjacent_matrix.hpp"
#include "weighted_adjacent_list.hpp"

int main()
{
    std::cout << "test_graph..." << std::endl;

    AdjacentMatrix::Test();
    AdjacentList::Test();
    WeightedAdjacentMatrix::Test();
    WeightedAdjacentList::Test();

    std::cout << "test done!" << std::endl << std::endl;

    return 0;
}