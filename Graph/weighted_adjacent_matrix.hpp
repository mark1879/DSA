#ifndef WEIGHTED_ADJACENT_MATRIX_HPP
#define WEIGHTED_ADJACENT_MATRIX_HPP
#include "weighted_graph.hpp"
#include <stack>
#include <queue>
#include <vector>
#include <gtest/gtest.h>
#include "Logger.hpp"

class WeightedAdjacentMatrix : public WeightedGraph
{
private:
    size_t vertex_count_;
    size_t edge_count_;
    std::vector<std::vector<int>> adjacent_matrix_;

public:
    const static int kIllegalWeight;

public:
    WeightedAdjacentMatrix(size_t veterx_count)
        : vertex_count_(veterx_count)
        , edge_count_(0)
    {
        adjacent_matrix_.resize(vertex_count_, std::vector<int>(vertex_count_, kIllegalWeight));
    }

    ~WeightedAdjacentMatrix()
    {}

    size_t VetextCount() const
    {
        return vertex_count_;
    }

    size_t EdgeCount() const
    {
        return edge_count_;
    }

    bool BFS(size_t start, std::vector<size_t>& order) const
    {
        if (start >= vertex_count_)
        {
            LOG_INFO("start is Out of Range");
            return false;
        }

        std::vector<bool> visited(vertex_count_, false);
        std::queue<size_t> queue;

        visited[start] = true;
        queue.push(start);

        while (!queue.empty())
        {
            auto current = queue.front();
            queue.pop();
            order.push_back(current);

            for (size_t i = 0; i < vertex_count_; i++)
            {
                if (adjacent_matrix_[current][i] != kIllegalWeight && !visited[i])
                {
                    visited[i] = true;
                    queue.push(i);
                }
            }
        }

        return true;
    }

    bool DFS(size_t start, std::vector<size_t>& order) const
    {
       if (start >= vertex_count_)
       {
            LOG_INFO("start is Out Of Range");
            return false;
       }

       std::vector<bool> visited(vertex_count_, false);
       std::stack<size_t> stack;

       stack.push(start);
       visited[start] = true;

       while (!stack.empty())
       {    
            auto current = stack.top();
            stack.pop();
            order.push_back(current);

            for (size_t i = 0; i < vertex_count_; i++)
            {
                if (adjacent_matrix_[current][i] != kIllegalWeight && !visited[i])
                {
                    stack.push(i);
                    visited[i] = true;
                }
            }
       }

       return true;
    }

    bool AddEdge(size_t src, size_t dst, int weight)
    {
        if (src >= vertex_count_ || dst >= vertex_count_)
        {
            LOG_INFO("src or dst is Out of Range");
            return false;
        }

        if (adjacent_matrix_[src][dst] != kIllegalWeight)
        {
            LOG_INFO("Edge already exists");
            return false;
        }

        adjacent_matrix_[src][dst] = weight;
        ++edge_count_;

        return true;
    }

    bool RemoveEdge(size_t src, size_t dst)
    {
        if (src >= vertex_count_ || dst >= vertex_count_)
        {
            LOG_INFO("src or dst is Out of Range");
            return false;
        }

        if (adjacent_matrix_[src][dst] == kIllegalWeight)
        {
            LOG_INFO("Edge does not exist");
            return false;
        }

        adjacent_matrix_[src][dst] = kIllegalWeight;
        --edge_count_;

        return true;
    }

    bool HasEdge(size_t src, size_t dst) const
    {
        if (src >= vertex_count_ || dst >= vertex_count_)
        {
            LOG_INFO("src or dst is Out of Range");
            return false;
        }

        return adjacent_matrix_[src][dst] != kIllegalWeight;
    }

    int  Weight(size_t src, size_t dst) const
    {
        if (src >= vertex_count_ || dst >= vertex_count_)
        {
            LOG_INFO("src or dst is Out of Range");
            return kIllegalWeight;
        }

        return adjacent_matrix_[src][dst];
    }

    static void Test()
    {
        std::cout << "WeightedAdjacentMatrix::Test()" << std::endl;

        WeightedGraph* graph = new WeightedAdjacentMatrix(8);

        // Test AddEdge
        EXPECT_EQ(graph->AddEdge(0, 1, 1), true);
        EXPECT_EQ(graph->AddEdge(0, 7, 7), true);
        EXPECT_EQ(graph->AddEdge(1, 3, 2), true);
        EXPECT_EQ(graph->AddEdge(1, 2, 1), true);
        EXPECT_EQ(graph->AddEdge(1, 5, 4), true);
        EXPECT_EQ(graph->AddEdge(2, 4, 2), true);
        EXPECT_EQ(graph->AddEdge(2, 6, 4), true);

        EXPECT_EQ(graph->AddEdge(2, 6, 4), false);
        EXPECT_EQ(graph->AddEdge(7, 8, 1), false);

        EXPECT_EQ(graph->VetextCount(), 8);
        EXPECT_EQ(graph->EdgeCount(), 7);

        // Test BFS
        std::vector<size_t> bfs_answer = {0, 1, 7, 2, 3, 5, 4, 6};
        std::vector<size_t> bfs_order;
        graph->BFS(0, bfs_order);

        EXPECT_EQ(bfs_answer.size(), bfs_order.size());
        for (size_t i = 0, size = bfs_order.size(); i < size; ++i)
        {
            EXPECT_EQ(bfs_answer[i], bfs_order[i]);
        }

        // Test DFS
        std::vector<size_t> dfs_answer = {0, 7, 1, 5, 3, 2, 6, 4};
        std::vector<size_t> dfs_order;
        graph->DFS(0, dfs_order);

        EXPECT_EQ(dfs_answer.size(), dfs_order.size());
        for (size_t i = 0, size = dfs_order.size(); i < size; ++i)
        {
            EXPECT_EQ(bfs_answer[i], bfs_order[i]);
        }

        // Test RemoveEdge
        EXPECT_EQ(graph->RemoveEdge(0, 1), true);
        EXPECT_EQ(graph->EdgeCount(), 6);
        EXPECT_EQ(graph->HasEdge(0, 1), false);

        EXPECT_EQ(graph->RemoveEdge(0, 1), false);
        EXPECT_EQ(graph->RemoveEdge(8, 9), false);
    }
};

const int WeightedAdjacentMatrix::kIllegalWeight = INT_MIN;

#endif