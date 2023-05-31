#include "adjacent_matrix.hpp"
#include "adjacent_list.hpp"
#include "weighted_adjacent_matrix.hpp"
#include "weighted_adjacent_list.hpp"
#include "dijkstra.hpp"
#include "dijkstra2.hpp"
#include "floyd.hpp"

int main()
{
    std::cout << "test_graph..." << std::endl;

    AdjacentMatrix::Test();
    AdjacentList::Test();
    WeightedAdjacentMatrix::Test();
    WeightedAdjacentList::Test();
    Dijkstra::Test();
    Dijkstra2::Test();
    Floyd::Test();

    std::cout << "test done!" << std::endl << std::endl;

    return 0;
}