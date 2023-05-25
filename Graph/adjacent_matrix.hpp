#include "graph.hpp"
#include <queue>
#include <stack>
#include <gtest/gtest.h>
#include "logger.hpp"

class AdjacentMatrix : public Graph
{
public:
    AdjacentMatrix(size_t vertex_count)
        : vertex_count_(vertex_count)
        , edge_count_(0)
    {
        adjacent_matrix_ = new bool*[vertex_count_];
        for (size_t i = 0; i < vertex_count_; ++i)
        {
            adjacent_matrix_[i] = new bool[vertex_count_];
            for (size_t j = 0; j < vertex_count_; ++j)
            {
                adjacent_matrix_[i][j] = false;
            }
        }
    }

    ~AdjacentMatrix()
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

    size_t VetextCount() const override
    { 
        return vertex_count_; 
    }

    size_t EdgeCount() const override
    { 
        return edge_count_; 
    }

   void BFS(size_t vertex, std::vector<size_t>& order) const override
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
                if (adjacent_matrix_[current_vertex][i] && !visited[i])
                {
                    queue.push(i);
                    visited[i] = true;
                }
            }
        }
   }

   void DFS(size_t vertex, std::vector<size_t>& order) const  override
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
                if (adjacent_matrix_[current_vertex][i] && !visited[i])
                {
                    stack.push(i);
                    visited[i] = true;
                }
            }
        }
   }

   bool AddEdge(size_t vertex1, size_t vertex2) override
   {
        if (vertex1 >= vertex_count_ || vertex2 >= vertex_count_)
        {
            LOG_INFO("Vertex out of range");
            return false;
        }

        if (adjacent_matrix_[vertex1][vertex2])
        {
            LOG_INFO("Edge already exists");
            return false;
        }

        adjacent_matrix_[vertex1][vertex2] = true;
        adjacent_matrix_[vertex2][vertex1] = true;
        ++edge_count_;

        return true;    
   }

   bool RemoveEdge(size_t vertex1, size_t vertex2) override
   {
        if (vertex1 >= vertex_count_ || vertex2 >= vertex_count_)
        {
            LOG_INFO("Vertex out of range");
            return false;
        }

        if (!adjacent_matrix_[vertex1][vertex2])
        {
            LOG_INFO("Edge does not exist");
            return false;
        }

        adjacent_matrix_[vertex1][vertex2] = false;
        adjacent_matrix_[vertex2][vertex1] = false;
        --edge_count_;

        return true;
   }

   bool HasEdge(size_t vertex1, size_t vertex2) const override
   {
        if (vertex1 >= vertex_count_ || vertex2 >= vertex_count_)
        {
            LOG_INFO("Vertex out of range");
            return false;
        }

        return adjacent_matrix_[vertex1][vertex2];
   }

   static void Test()
   {
        std::cout << "AdjacentMatrix::Test()" << std::endl;

        Graph* graph = new AdjacentMatrix(8);

        // Test AddEdge
        EXPECT_EQ(graph->AddEdge(0, 1), true);
        EXPECT_EQ(graph->AddEdge(0, 7), true);
        EXPECT_EQ(graph->AddEdge(1, 3), true);
        EXPECT_EQ(graph->AddEdge(1, 2), true);
        EXPECT_EQ(graph->AddEdge(1, 5), true);
        EXPECT_EQ(graph->AddEdge(2, 4), true);
        EXPECT_EQ(graph->AddEdge(2, 6), true);

        EXPECT_EQ(graph->AddEdge(2, 6), false);
        EXPECT_EQ(graph->AddEdge(7, 8), false);

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
    bool** adjacent_matrix_;
};