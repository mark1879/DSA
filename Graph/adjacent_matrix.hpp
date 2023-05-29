#include "graph.hpp"
#include <queue>
#include <stack>
#include <gtest/gtest.h>
#include <vector>
#include "logger.hpp"

class AdjacentMatrix : public Graph
{
private:
    size_t vertex_count_;
    size_t edge_count_;
    std::vector<std::vector<bool>> adjacent_matrix_;

public:
    AdjacentMatrix(size_t vertex_count)
        : vertex_count_(vertex_count)
        , edge_count_(0)
    {
        adjacent_matrix_.resize(vertex_count, std::vector<bool>(vertex_count, false));
    }

    ~AdjacentMatrix()
    {}

    size_t VertexCount() const override
    { 
        return vertex_count_; 
    }

    size_t EdgeCount() const override
    { 
        return edge_count_; 
    }

    bool BFS(size_t start, std::vector<size_t>& order) const override
    {
        if (start >= vertex_count_)
        {
            LOG_INFO("start is Out of Range");
            return false;
        }

        std::vector<bool> visited(vertex_count_, false);
        std::queue<size_t> queue;

        queue.push(start);
        visited[start] = true;

        while (!queue.empty())
        {
            auto current = queue.front();
            queue.pop();
            order.push_back(current);

            for (size_t i = 0; i < vertex_count_; i++)
            {
                if (adjacent_matrix_[current][i] && !visited[i])
                {
                    queue.push(i);
                    visited[i] = true;
                }
            }
        }

        return true;
    }

   bool DFS(size_t start, std::vector<size_t>& order)  const override
   {
        if (start >= vertex_count_)
        {
            LOG_INFO("start is Out of Range");
            return false;
        }

        std::vector<bool> visited(vertex_count_, false);
        std::stack<size_t> stack;

        stack.push(start);
        visited[start] = true;

        while (!stack.empty())
        {
            size_t current = stack.top();
            stack.pop();
            order.push_back(current);

            for (size_t i = 0; i < vertex_count_; ++i)
            {
                if (adjacent_matrix_[current][i] && !visited[i])
                {
                    stack.push(i);
                    visited[i] = true;
                }
            }
        }

        return true;
   }

   bool AddEdge(size_t src, size_t dst) override
   {
        if (src >= vertex_count_ || dst >= vertex_count_)
        {
            LOG_INFO("src or dst is Out of Range");
            return false;
        }

        if (adjacent_matrix_[src][dst])
        {
            LOG_INFO("Edge already exists");
            return false;
        }

        adjacent_matrix_[src][dst] = true;
        adjacent_matrix_[dst][src] = true;
        ++edge_count_;

        return true;    
   }

   bool RemoveEdge(size_t src, size_t dst) override
   {
       if (src >= vertex_count_ || dst >= vertex_count_)
        {
            LOG_INFO("src or dst is Out of Range");
            return false;
        }

        if (!adjacent_matrix_[src][dst])
        {
            LOG_INFO("Edge does not exist");
            return false;
        }

        adjacent_matrix_[src][dst] = false;
        adjacent_matrix_[src][dst] = false;
        --edge_count_;

        return true;
   }

   bool HasEdge(size_t src, size_t dst) const override
   {
        if (src >= vertex_count_ || dst >= vertex_count_)
        {
            LOG_INFO("src or dst is Out of Range");
            return false;
        }

        return adjacent_matrix_[src][dst] && adjacent_matrix_[dst][src];
   }

    bool ShortestPath(size_t start, size_t end, std::vector<size_t>& path) const override
    {
        if (start >= vertex_count_ || end >= vertex_count_)
        {
            LOG_INFO("start or end is Out of Range");
            return false;
        }
        
        std::vector<bool> visited(vertex_count_, false);
        std::queue<size_t> queue;
        std::vector<size_t> parents(vertex_count_, INT_MAX);

        visited[start] = true;
        queue.push(start);

        while (!queue.empty())
        {
            auto current = queue.front();
            queue.pop();
            
            if (current == end)
                break;

            for (size_t i = 0; i < vertex_count_; i++)
            {
                if (adjacent_matrix_[current][i] && !visited[i])
                {
                    queue.push(i);
                    visited[i] = true;
                    parents[i] = current;
                }
            }
        }

        if (!visited[end])
        {
            LOG_INFO("There is no path: %lu -> %lu", start, end);
            return false;
        }

        auto current = end;
        while (current != start)
        {
            path.push_back(current);
            current = parents[current];
        }

        path.push_back(start);
        std::reverse(path.begin(), path.end());
     
        return true;
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

        EXPECT_EQ(graph->VertexCount(), 8);
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

         // Test ShortestPath
        std::vector<size_t> shortest_path;
        std::vector<size_t> shortest_path_answer = {0, 1, 3};
        graph->ShortestPath(0, 3, shortest_path);

        EXPECT_EQ(shortest_path.size(), shortest_path_answer.size());
        for (size_t i = 0, size = shortest_path.size(); i < size; i++)
        {
            EXPECT_EQ(shortest_path[i], shortest_path_answer[i]);
        }

        // Test RemoveEdge
        EXPECT_EQ(graph->RemoveEdge(0, 1), true);
        EXPECT_EQ(graph->EdgeCount(), 6);
        EXPECT_EQ(graph->HasEdge(0, 1), false);

        EXPECT_EQ(graph->RemoveEdge(0, 1), false);
        EXPECT_EQ(graph->RemoveEdge(8, 9), false);
   }
};