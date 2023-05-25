#include "adjacent_matrix.hpp"
#include "weighted_adjacent_matrix.hpp"

int main()
{
    std::cout << "test_graph..." << std::endl;

    AdjacentMatrix::Test();
    WeightedAdjacentMatrix::Test();

    std::cout << "test done!" << std::endl << std::endl;

    return 0;
}