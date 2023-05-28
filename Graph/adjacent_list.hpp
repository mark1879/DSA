#ifndef ADJACENT_LIST_HPP
#define ADJACENT_LIST_HPP
#include "graph.hpp"
#include "Logger.hpp"
#include <vector>
#include <list>
#include <queue>
#include <stack>
#include <gtest/gtest.h>

class AdjacentList : public Graph
{
private:
    size_t vertex_count_;
    size_t edge_count_;
    std::vector<std::vector<size_t>> adjacent_list_;

public:
    AdjacentList(size_t vertex_count)
        : vertex_count_(vertex_count)
        , edge_count_(0)
    {
       adjacent_list_.resize(vertex_count_);
    }

    ~AdjacentList()
    {}

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

            for (size_t i = 0; i < adjacent_list_[current_vertex].size(); ++i)
            {
                size_t adjacent_vertex = adjacent_list_[current_vertex][i];
                if (!visited[adjacent_vertex])
                {
                    queue.push(adjacent_vertex);
                    visited[adjacent_vertex] = true;
                }
            }
        }
    }

    void DFS(size_t vertex, std::vector<size_t>& order) const override
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

            for (size_t i = 0; i < adjacent_list_[current_vertex].size(); ++i)
            {
                size_t adjacent_vertex = adjacent_list_[current_vertex][i];
                if (!visited[adjacent_vertex])
                {
                    stack.push(adjacent_vertex);
                    visited[adjacent_vertex] = true;
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

        for (size_t i = 0; i < adjacent_list_[vertex1].size(); ++i)
        {
            if (adjacent_list_[vertex1][i] == vertex2)
            {
                LOG_INFO("Edge already exists");
                return false;
            }
        }

        adjacent_list_[vertex1].push_back(vertex2);
        adjacent_list_[vertex2].push_back(vertex1);
        ++edge_count_;

        return true;
    }

    bool RemoveEdge(size_t vertex1, size_t vertex2)
    {
        if (vertex1 >= vertex_count_ || vertex2 >= vertex_count_)
        {
            LOG_INFO("Vertex out of range");
            return false;
        }

        bool deleted = false;

        for (size_t i = 0; i < adjacent_list_[vertex1].size(); ++i)
        {
            if (adjacent_list_[vertex1][i] == vertex2)
            {
                deleted = true;
                adjacent_list_[vertex1].erase(adjacent_list_[vertex1].begin() + i);
                break;
            }
        }

        if (!deleted)
        {
            LOG_INFO("Edge does not exist");
            return false;
        }

        for (size_t i = 0; i < adjacent_list_[vertex2].size(); ++i)
        {
            if (adjacent_list_[vertex2][i] == vertex1)
            {
                adjacent_list_[vertex2].erase(adjacent_list_[vertex2].begin() + i);
                break;
            }
        }

        --edge_count_;

        return deleted;
    }

    bool HasEdge(size_t vertex1, size_t vertex2) const
    {
        if (vertex1 >= vertex_count_ || vertex2 >= vertex_count_)
        {
            LOG_INFO("Vertex out of range");
            return false;
        }

        for (size_t i = 0; i < adjacent_list_[vertex1].size(); ++i)
        {
            if (adjacent_list_[vertex1][i] == vertex2)
            {
                return true;
            }
        }

        return false;
    }

    void ShortestPath(size_t start, size_t end, std::vector<size_t>& path) const
    {
        std::vector<bool> visited(vertex_count_, false);
        std::vector<size_t> prev(vertex_count_, INT_MAX);
        std::queue<size_t> queue;

        queue.push(start);
        visited[start] = true;

        while (!queue.empty())
        {
            size_t current_vertex = queue.front();
            if (current_vertex == end)
            {
                break;
            }

            queue.pop();

            for (size_t i = 0; i < adjacent_list_[current_vertex].size(); ++i)
            {
                size_t adjacent_vertex = adjacent_list_[current_vertex][i];
                if (!visited[adjacent_vertex])
                {
                    queue.push(adjacent_vertex);
                    visited[adjacent_vertex] = true;
                    prev[adjacent_vertex] = current_vertex;
                }
            }
        }

        if (!visited[end])
        {
            LOG_INFO("No path from {} to {}", start, end);
            return;
        }

        size_t current_vertex = end;
        while (current_vertex != start)
        {
            path.push_back(current_vertex);
            current_vertex = prev[current_vertex];
        }

        path.push_back(start);
        std::reverse(path.begin(), path.end());
    }

     static void Test()
   {
        std::cout << "AdjacentList::Test()" << std::endl;

        Graph* graph = new AdjacentList(8);

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
        std::vector<size_t> bfs_answer = {0, 1, 7, 3, 2, 5, 4, 6};
        std::vector<size_t> bfs_order;
        graph->BFS(0, bfs_order);

        EXPECT_EQ(bfs_answer.size(), bfs_order.size());
        for (size_t i = 0, size = bfs_order.size(); i < size; ++i)
        {
            EXPECT_EQ(bfs_answer[i], bfs_order[i]);
        }

        // Test DFS
        std::vector<size_t> dfs_answer = {0, 7, 1, 5, 2, 6, 4, 3};
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

#endif