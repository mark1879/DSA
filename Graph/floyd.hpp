#ifndef FLOYD_HPP
#define FLOYD_HPP
#include "weighted_graph.hpp"
#include "weighted_adjacent_matrix.hpp"
#include "Logger.hpp"

class Floyd
{
public:
     Floyd(const std::shared_ptr<WeightedGraph>& graph)
        : graph_(graph)
    {
        size_t vertex_count = graph->VertexCount();
        dist_.resize(vertex_count, std::vector<int>(vertex_count, WeightedGraph::kIllegalWeight));

        // 复制边
        for (size_t i = 0; i < vertex_count; i++)
        {
            for (size_t j = 0; j < vertex_count; j++)
            {
                dist_[i][j] = graph_->Weight(i, j);
            }
        }

        // 松弛边
        for (size_t k = 0; k < vertex_count; k++)
        {
            for (size_t i = 0; i < vertex_count; i++)
            {
                for (size_t j = 0; j < vertex_count; j++)
                {
                    if (dist_[i][k] != WeightedGraph::kIllegalWeight 
                            && dist_[k][j] != WeightedGraph::kIllegalWeight)
                    {
                        dist_[i][j] = std::min(dist_[i][j], dist_[i][k] + dist_[k][j]);
                    }
                }
            }
        }
    }

    void Print()
    {
        for (auto i : dist_)
        {
            for (auto j : i)
                std::cout << j << "\t\t\t";

            std::cout << std::endl;
        }

    }

    int Dist(size_t src, size_t dst)
    {
        if (src >= graph_->VertexCount() || dst >= graph_->VertexCount())
        {
            LOG_INFO("src or dst is Out of Range");
            return WeightedGraph::kIllegalWeight;
        }

        return dist_[src][dst];
    }

    static void Test()
    {

        std::cout << "Floyd::Test()" << std::endl;

        std::shared_ptr<WeightedGraph> graph = std::make_shared<WeightedAdjacentMatrix>(7);

        EXPECT_EQ(graph->AddEdge(0, 1, 1), true);
        EXPECT_EQ(graph->AddEdge(0, 6, 10), true);
        EXPECT_EQ(graph->AddEdge(1, 3, 2), true);
        EXPECT_EQ(graph->AddEdge(1, 2, 2), true);
        EXPECT_EQ(graph->AddEdge(2, 4, 2), true);
        EXPECT_EQ(graph->AddEdge(2, 6, 2), true);

        Floyd floyd(graph);

        EXPECT_EQ(floyd.Dist(0, 6), 5);
        EXPECT_EQ(floyd.Dist(1, 4), 4);
    }

private:
    std::shared_ptr<WeightedGraph> graph_;
    std::vector<std::vector<int>> dist_;
};

#endif