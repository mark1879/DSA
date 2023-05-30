#ifndef DIJKSTRA2_HPP
#define DIJKSTRA2_HPP
#include "weighted_graph.hpp"
#include "weighted_adjacent_matrix.hpp"
#include <vector>
#include <memory>
#include <iostream>
#include <gtest/gtest.h>
#include "Logger.hpp"

class Dijkstra2
{
public:
    Dijkstra2(const std::shared_ptr<WeightedGraph>& graph, size_t src)
        : graph_(graph)
    {
        size_t vertex_count = graph->VertexCount();

        if (src >= vertex_count)
            LOG_FATAL("src is Out of Range!");

         std::vector<bool> visited;
        // pair<weight, vertex>
        // 库函数 greater 默认按 key排序
        std::priority_queue<std::pair<int, size_t>, std::vector<std::pair<int, size_t>>, std::greater<std::pair<int, size_t>>> small_heap_;
        
        visited.resize(vertex_count, false);
        dist_.resize(vertex_count, WeightedGraph::kIllegalWeight);
        dist_[src] = 0;

        small_heap_.push(std::make_pair(0, src));

        while (!small_heap_.empty())
        {
            size_t top = small_heap_.top().second;
            small_heap_.pop();

            if (visited[top])
                continue;

            visited[top] = true;

            for (size_t i = 0; i < vertex_count; i++)
            {
                if (!visited[i] 
                        && graph->Weight(top, i) != WeightedGraph::kIllegalWeight
                        && (dist_[top] + graph->Weight(top, i)) < dist_[i])
                {
                    dist_[i] = dist_[top] + graph->Weight(top, i);
                    small_heap_.push(std::make_pair(graph->Weight(top, i), i));
                }
            }
        }
    }

    int DistTo(size_t dst)
    {
        if (dst >= graph_->VertexCount())
        {
            LOG_INFO("dst is Out Of Range!");
            return WeightedGraph::kIllegalWeight;
        }

        return dist_[dst];
    }

    static void Test()
    {
        std::cout << "Dijkstra2::Test()" << std::endl;

        std::shared_ptr<WeightedGraph> graph = std::make_shared<WeightedAdjacentMatrix>(8);

        // Test AddEdge
        EXPECT_EQ(graph->AddEdge(0, 1, 1), true);
        EXPECT_EQ(graph->AddEdge(0, 7, 10), true);
        EXPECT_EQ(graph->AddEdge(1, 3, 2), true);
        EXPECT_EQ(graph->AddEdge(1, 2, 2), true);
        EXPECT_EQ(graph->AddEdge(2, 4, 2), true);
        EXPECT_EQ(graph->AddEdge(2, 6, 2), true);

        Dijkstra2 dijkstra2(graph, 0);

        EXPECT_EQ(dijkstra2.DistTo(1), 1);
        EXPECT_EQ(dijkstra2.DistTo(6), 5);
    }

private:
    std::shared_ptr<WeightedGraph> graph_;
    std::vector<int> dist_;
};

#endif