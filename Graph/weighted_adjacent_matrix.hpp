#ifndef WEIGHTED_ADJACENT_MATRIX_HPP
#define WEIGHTED_ADJACENT_MATRIX_HPP
#include "weighted_graph.hpp"
#include <stack>
#include <queue>
#include <gtest/gtest.h>

class WeightedAdjacentMatrix : public WeightedGraph
{
public:
    WeightedAdjacentMatrix(size_t veterx_count)
        : vertex_count_(veterx_count)
        , edge_count_(0)
    {
        adjacent_matrix_ = new int*[vertex_count_];
        for (size_t i = 0; i < vertex_count_; ++i)
        {
            adjacent_matrix_[i] = new int[vertex_count_];
            for (size_t j = 0; j < vertex_count_; ++j)
            {
                adjacent_matrix_[i][j] = kNoEdge;
            }
        }
    }

    ~WeightedAdjacentMatrix()
    {
        if (adjacent_matrix_ != nullptr)
        {
            for (size_t i = 0; i < vertex_count_; ++i)
            {
                delete[] adjacent_matrix_[i];
            }
            delete[] adjacent_matrix_;
        }
    }

    size_t VetextCount() const
    {
        return vertex_count_;
    }

    size_t EdgeCount() const
    {
        return edge_count_;
    }

    void BFS(size_t vertex, std::vector<size_t>& order) const
    {
        std::vector<bool> visited(vertex_count_, false);
        std::queue<size_t> queue;

        queue.push(vertex);
        visited[vertex] = true;

        while (!queue.empty())
        {
            size_t current_vertex = queue.front();
            queue.pop();
            order.push_back(current_vertex);

            for (size_t i = 0; i < vertex_count_; ++i)
            {
                if (adjacent_matrix_[current_vertex][i] != kNoEdge && !visited[i])
                {
                    queue.push(i);
                    visited[i] = true;
                }
            }
        }
    }


    void DFS(size_t vertex, std::vector<size_t>& order) const
    {
        std::vector<bool> visited(vertex_count_, false);
        std::stack<size_t> stack;

        stack.push(vertex);
        visited[vertex] = true;

        while (!stack.empty())
        {
            size_t current_vertex = stack.top();
            stack.pop();
            order.push_back(current_vertex);

            for (size_t i = 0; i < vertex_count_; ++i)
            {
                if (adjacent_matrix_[current_vertex][i] != kNoEdge && !visited[i])
                {
                    stack.push(i);
                    visited[i] = true;
                }
            }
        }
    }


    bool AddEdge(size_t vertex1, size_t vertex2, int weight)
    {
        if (vertex1 >= vertex_count_ || vertex2 >= vertex_count_)
        {
            LOG_INFO("vertex1 or vertex2 is out of range");
            return false;
        }

        if (adjacent_matrix_[vertex1][vertex2] != kNoEdge)
        {
            LOG_INFO("Edge already exists");
            return false;
        }

        adjacent_matrix_[vertex1][vertex2] = weight;
        ++edge_count_;

        return true;
    }

    bool RemoveEdge(size_t vertex1, size_t vertex2)
    {
        if (vertex1 >= vertex_count_ || vertex2 >= vertex_count_)
        {
            LOG_INFO("vertex1 or vertex2 is out of range");
            return false;
        }

        if (adjacent_matrix_[vertex1][vertex2] == kNoEdge)
        {
            LOG_INFO("Edge does not exist");
            return false;
        }

        adjacent_matrix_[vertex1][vertex2] = kNoEdge;
        --edge_count_;

        return true;
    }

    bool HasEdge(size_t vertex1, size_t vertex2) const
    {
        if (vertex1 >= vertex_count_ || vertex2 >= vertex_count_)
        {
            return false;
        }

        return adjacent_matrix_[vertex1][vertex2] != kNoEdge;
    }


    int  Weight(size_t vertex1, size_t vertex2) const
    {
        if (vertex1 >= vertex_count_ || vertex2 >= vertex_count_)
        {
            return kNoEdge;
        }

        return adjacent_matrix_[vertex1][vertex2];

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

private:
    size_t vertex_count_;
    size_t edge_count_;
    int** adjacent_matrix_;
    int kNoEdge = 0;
};


#endif