#ifndef DIJKSTRA_HPP
#define DIJKSTRA_HPP
#include "weighted_graph.hpp"
#include "weighted_adjacent_matrix.hpp"
#include <vector>
#include <memory>
#include <iostream>
#include <gtest/gtest.h>
#include "Logger.hpp"

class Dijkstra
{
public:
    Dijkstra(const std::shared_ptr<WeightedGraph>& graph, size_t src)
        : graph_(graph)
    {
        size_t vertex_count = graph->VertexCount();

        if (src >= vertex_count)
            LOG_FATAL("src is Out of Range!");
        
        visited_.resize(vertex_count, false);
        dist_.resize(vertex_count, WeightedGraph::kIllegalWeight);

        dist_[0] = 0;

        for (size_t i = 0; i < vertex_count; i++)
        {
            size_t closest_vertex = ClosestVertexToSrc();
            if (closest_vertex == WeightedGraph::kIllegalVertex)
                break;

            visited_[closest_vertex] = true;

            for (size_t i = 0; i < vertex_count; i++)
            {
                if (!visited_[i] 
                        && graph->Weight(closest_vertex, i) != WeightedGraph::kIllegalWeight
                        && (dist_[closest_vertex] + graph->Weight(closest_vertex, i)) < dist_[i])
                {
                    dist_[i] = dist_[closest_vertex] + graph->Weight(closest_vertex, i);
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
        std::cout << "Dijkstra::Test()" << std::endl;

        std::shared_ptr<WeightedGraph> graph = std::make_shared<WeightedAdjacentMatrix>(8);

        // Test AddEdge
        EXPECT_EQ(graph->AddEdge(0, 1, 1), true);
        EXPECT_EQ(graph->AddEdge(0, 7, 10), true);
        EXPECT_EQ(graph->AddEdge(1, 3, 2), true);
        EXPECT_EQ(graph->AddEdge(1, 2, 2), true);
        EXPECT_EQ(graph->AddEdge(2, 4, 2), true);
        EXPECT_EQ(graph->AddEdge(2, 6, 2), true);

        Dijkstra dijkstra(graph, 0);

        EXPECT_EQ(dijkstra.DistTo(1), 1);
        EXPECT_EQ(dijkstra.DistTo(6), 5);
    }

private:
    size_t ClosestVertexToSrc()
    {   
        // illegal vertex
        size_t closest_vertex = WeightedGraph::kIllegalVertex;
        // illegal distance
        int closest_dist = WeightedGraph::kIllegalWeight;

        for (size_t i = 0, count = graph_->VertexCount(); i < count; i++)
        {
            if (!visited_[i] && dist_[i] < closest_dist)
            {
                closest_vertex = i;
                closest_dist = dist_[i];
            }
        }

        return closest_vertex;
    }

private:
    std::shared_ptr<WeightedGraph> graph_;
    std::vector<bool> visited_;
    std::vector<int> dist_;
};

#endif